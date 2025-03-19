#ifndef SCENE_H
#define SCENE_H

#include "addons.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>

void draw_sidebar(SDL_Window* window, SDL_Renderer* renderer);

void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b);

#endif