#!/usr/bin/node

"use strict";
const FileSystem           = require('fs');
const childProcess         = require('child_process');
const exec                 = childProcess.execSync;
const spawn                = childProcess.spawn;
const crypto               = require('crypto');
const OS                   = require('os');
const readline             = require("readline");


// force ground color
var fg = 
{
    reset : '\x1B[0m',
    black : '\x1B[30m',
    darkred : '\x1B[31m',
    darkgreen : '\x1B[32m',
    orange : '\x1B[33m',
    darkblue : '\x1B[34m',
    purple : '\x1B[35m',
    darkcyan : '\x1B[36m',
    gray : '\x1B[37m',
    darkgray : '\x1B[90m',
    red : '\x1B[91m',
    green : '\x1B[92m',
    yellow : '\x1B[93m',
    blue : '\x1B[94m',
    pink : '\x1B[95m',
    cyan : '\x1B[96m'
};

var print = s => process.stdout.write(s);

var currentLine = 0;

function echo(s, color="")
{
    // clear line if line is new
    if(s.match(/\n$/))
    {
        readline.clearLine(process.stdout, 2);
    }
    
    if(color != "")
    {
        s = color + s + fg.reset;
    }
    print(s);

    return currentLine;
}

function display(s)
{
    readline.cursorTo(process.stdout, 0, null);
    readline.clearLine(process.stdout, 0);
    print("\n");
    print(s);
    readline.cursorTo(process.stdout, 0, null);
    readline.moveCursor(process.stdout, 0, -1);
}

var performance =
{
    "now" : function()
    {
        var t = process.hrtime();
        return t[0] + t[1]/1e9;
    }
};


var remove = function(value, arr)
{
    var index = arr.indexOf(value);
    arr.splice(index, 1);
    return arr;
};

//setup for compile
// ../App_Win32/src
var sources = scandir("../App_Win32/src").filter(file => file.match(/\.cpp$/));

var includes = "-I ../Libraries/SDL2/include -I ../Include";
var libraries = " lib/libSDL2.bc lib/libGame.bc lib/libBox2D.bc lib/libFreeType2.bc lib/libJSON.bc lib/libMisc.bc ";
var flags = "-O1 -g -std=c++11";
var cc = "em++";
if(OS.platform() == "win32")
{
    cc = "em++.bat";
}
var programName = "-o bin/Bounce.html";
var link = "em++";
var link_flags = "-O1";
var link_options = "-s ALLOW_MEMORY_GROWTH=1 -s ASM_JS=1 -s USE_WEBGL2=1 -s FULL_ES2=1 -s ASSERTIONS=1 -s GL_FFP_ONLY=1 --use-preload-plugins --preload-file ../Resources@/Resources ";

echo ("\n");
echo ("-- Compiling --\n\n", fg.cyan);

var objects = [];
var build = true;

var commands = [];
var cp_times = [];

for(var i in sources)
{
    var c = sources[i];
    var o = "obj/" + i + ".bc";
    objects.push(o);
    commands.push({file: c , line: [cc, ...flags.split(" ") , "-c" , c , ...includes.split(" "), "-o" , o ]});

}

var uncompiled_files = commands.length;
var uncached_files = uncompiled_files;
var compiling_files = [];

function compile()
{
    if(commands.length > 0)
    {
        var command = commands.pop();
        var id   = commands.length;
        var file = command.file;
        var file1 = "obj/" + id + ".cache";
        var onCompleted = function(id, is_cached)
        {
            var t1 = cp_times[id];
            var t2 = performance.now();
            var time = Math.round((t2 - t1)*1000)/1000;
            echo(`    Compiled ${fg.pink}"${command.file}"${fg.reset}`);
            uncompiled_files--;
            remove(command.file, compiling_files);

            if(is_cached)
            {
                echo(` ${fg.darkgray}(cached)${fg.reset}`);
                uncached_files--;
            }
            else
            {
                echo(` ${fg.orange}(${time}s)${fg.reset} ${fg.green}(success)${fg.reset}`);
            }
            echo("\n");
            if(uncompiled_files < 1)
            {
                linkProgram();
                return;
            }
            else
            {
                // execute next command
                compile();
            }

        };
        
        if(!fileExists(file1) || (md5f(file1) != md5f(file)))
        {

            compiling_files.push(command.file);
            display(`Compiling ... ${id} files: ${fg.yellow}${compiling_files[0]}${fg.reset}`);

            cp_times[id] = performance.now();
            // stdio: "inherit" to keep color by child process
            var child_process = spawn(command.line[0], command.line.slice(1) , {stdio: "inherit", encoding: "utf-8" });
            
            child_process.on("error", function(e) { console.log(e);});
            child_process.on('close', function(exitcode)
            {
                onCompleted(id, false);
                copyfile(file, file1);
            });
        }
        else
        {
            onCompleted(id, true);
        }

    }
}

// 4 process at the same time
for(var i = 0; i < 4; i++)
{
    compile();
}

function linkProgram()
{
    
    echo("\n");
    echo("-- BUILD COMPLETE --\n\n");
    
    var link_cmd = [link, link_flags, link_options , objects.join(" "), libraries, programName].join(" ");
    
    echo ("\n");
    echo ("-- Linking program --\n", fg.cyan);
    //if(uncached_files > 0)
    {
        exec(link_cmd);
    }
    echo ("-- Done --\n\n", fg.cyan);
}


///////////////////////////////////////////////////////////////////

function scandir(dir)
{
    var result = [];
    var list = FileSystem.readdirSync(dir).map(file => dir + "/" + file);
    while(list.length > 0)
    {
        var file = list.pop();
        if(FileSystem.lstatSync(file).isDirectory())
        {
            var t = FileSystem.readdirSync(file);
            for(var child of t)
            {
                list.push(file + "/" + child);
            }
        }
        else
        {
            result.push(file);
        }
    }
    return result;
}

function copyfile(source, target)
{
    FileSystem.createReadStream(source).pipe(FileSystem.createWriteStream(target));
}

function fileExists(file)
{
    return FileSystem.existsSync(file);
}

function md5f(file)
{
    var data = FileSystem.readFileSync(file);
    return crypto.createHash('md5').update(data).digest("hex");
}

///////////////////////////////////////////////////////////////////