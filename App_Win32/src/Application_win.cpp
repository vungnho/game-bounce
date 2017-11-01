#include <SDL2/SDL_test_common.h>

#include "stdafx.h"
//#include <Utilities/MemoryOperators.h>
#include "../../Game/Globals.h"
#include <stdlib.h>
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#undef main

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "game/EventListenerCenter.h"

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
    EventListenerCenterS::GetInstance()->Update();
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

    /* Set the correct attributes for MASK and MAJOR version */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#pragma region APP_INIT

    //Create window, TODO: Make it better
    SDL_Window*  sdl_Window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        700, 700, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
        if (gContext == NULL)
        {
            printf("gContext == NULL ! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Use Vsync 
            if (SDL_GL_SetSwapInterval(0) < 0)
            {
                printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
            }
            //Initialize OpenGL 
            if (!initGL())
            {
                printf("Unable to initialize OpenGL!\n");
                success = false;
            }
        }
    }

    // Init Game Components
    GameInit();
    //
    EventListenerCenterS::GetInstance();

#pragma endregion APP_INIT

    //Main loop flag
    bool running = true;

#ifdef __EMSCRIPTEN__
    // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
    emscripten_set_main_loop(__main_loop__, 30, 1);
#else
    //While application is running
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYUP)
            {
                OnKeyEvent(event.key.keysym.sym, false);
            }
            if (event.type == SDL_KEYDOWN)
            {
                OnKeyEvent(event.key.keysym.sym, true);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                OnTouchEvent(TOUCH_ACTION_DOWN, x, y, 0);
            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                OnTouchEvent(TOUCH_ACTION_UP, x, y, 0);
                printf(" --> called OnMouseUp(%d, %d)\n", x, y);
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                OnTouchEvent(TOUCH_ACTION_MOVE, x, y, 0);
            }
        }

        __main_loop__();
        SDL_GL_SwapWindow(sdl_Window);
        //Wait 100 miliseconds
        SDL_Delay(20);
        

    }

#endif
    //Quit SDL subsystems
    SDL_Quit();

    //identifying memory leaks
    //MemoryDump();
    printf("Press any key...\n");
    //_getch();

    return 0;

}


