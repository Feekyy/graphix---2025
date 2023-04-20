#include "circle.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
	Circle circle;
	double area;
	bool quit = false;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window * window = SDL_CreateWindow("SDL2 line drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
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
		set_circle_data(&circle, 5, 10, 8);
		area = calc_circle_area(&circle);

		draw_circle(&circle, 80, &renderer);

		printf("Circle area: %lf\n", area);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
