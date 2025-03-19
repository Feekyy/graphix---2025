#include "app.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_GLContext gl_context = NULL;
    SDL_Renderer* renderer = NULL;

    int init_result = initialize_app(&window, &gl_context, &renderer);
    if (init_result != 0) 
    {
        printf("Failed to initialize app: %d\n", init_result);
        return 1;
    }

    run_app(window, renderer);
    cleanup_app(window, gl_context, renderer);

    return 0;
}