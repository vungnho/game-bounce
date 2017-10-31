

#include "stdafx.h"
//#include <Utilities/MemoryOperators.h>
#include "../Game/Globals.h"
#include <conio.h>
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#undef main

extern int  GameInit();
extern void GameDraw();
extern void GameUpdate(float);
extern void OnKeyEvent(unsigned char, bool);
extern void GameCleanUp();
extern void OnTouchEvent(int type, int x, int y, int id);

static const int TOUCH_ACTION_UP = 0;
static const int TOUCH_ACTION_DOWN = 1;
static const int TOUCH_ACTION_MOVE = 2;


void __main_loop__()
{
    //Handle events on queue
    GameUpdate(0.04);
    GameDraw();

}

bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;


    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL! %s\n", "gluErrorString(error)");
        success = false;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL! %s\n", "gluErrorString(error)");
        success = false;
    }

    return success;
}

void AppInit()
{
    //Create window, TODO: Make it better
    SDL_Window*  sdl_Window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (sdl_Window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //SDL_Surface* surface = SDL_GetWindowSurface(sdl_Window);
        //Create context
        SDL_GLContext gContext = SDL_GL_CreateContext(sdl_Window);
        int success = false;
        if( gContext == NULL )
        {
            printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Use Vsync 
            if( SDL_GL_SetSwapInterval( 1 ) < 0 )
            {
                printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
            }
            //Initialize OpenGL 
            if( !initGL() )
            {
                printf( "Unable to initialize OpenGL!\n" );
                success = false;
            }
        }
    }

}

int main(int argc, const char * argv[])
{
    int a = 1;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    AppInit();


    //Main loop flag
    bool running = true;

#ifdef __EMSCRIPTEN__
    // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
    emscripten_set_main_loop(__main_loop__, 30, 1);
#else
    //While application is running
    while (running)
    {
        __main_loop__();
        //Wait 100 miliseconds
        SDL_Delay(20);

    }

#endif
    //Quit SDL subsystems
    SDL_Quit();

    //identifying memory leaks
    //MemoryDump();
    printf("Press any key...\n");
    _getch();

    return 0;

}


