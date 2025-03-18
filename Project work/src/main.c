#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <stdbool.h>
#include <stdio.h>

#include "app.h"
#include "addons.h"

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_GLContext gl_context = NULL;
    SDL_Renderer* renderer = NULL;

    if (initialize_app(&window, &gl_context, &renderer) == 0) 
    {
        run_app(window, renderer);
        cleanup_app(window, gl_context, renderer);
    }

    return 0;
}


