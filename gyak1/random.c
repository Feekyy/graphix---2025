#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define HEIGHT 600
#define WIDTH 800

int main(int argc, char* argv[])
{
  int error_code;
  SDL_Window* window;
  bool need_run;
  SDL_Event event;
  SDL_Renderer* renderer;

  int xMouse = 0;
  int yMouse = 0;
  int point_count = 0;
  int line_count = 0;

  int tmpX = 0;
  int tmpY = 0;

  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0) {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow(
    "Hello SDL!",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
}
