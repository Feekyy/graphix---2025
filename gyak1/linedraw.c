#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int mouseX;
int mouseY;

int main(int argc, char ** argv)
{

    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("SDL2 line drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    while (!quit)
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        if (SDL_MOUSEBUTTONDOWN)
        {
          SDL_GetMouseState(&mouseX, &mouseY);
          printf("Mouse's X: %d\nMouse's Y: %d\n", mouseX, mouseY);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawLine(renderer, 0, 0, 100, 100);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
