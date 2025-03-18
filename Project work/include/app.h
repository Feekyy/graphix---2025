#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int initialize_app(SDL_Window** window, SDL_GLContext* gl_context);
void run_app(SDL_Window* window, SDL_Renderer* renderer);
void cleanup_app(SDL_Window* window, SDL_GLContext gl_context, SDL_Renderer* renderer);

#endif