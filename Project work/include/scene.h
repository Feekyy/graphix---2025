#ifndef SCENE_H
#define SCENE_H

#include "addons.h"
#include <SDL2/SDL.h>

void draw_sidebar(SDL_Renderer* renderer, SDL_Texture* line_icon, SDL_Texture* square_icon);

void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b);

SDL_Texture* load_texture(const char* path, SDL_Renderer* renderer);

#endif