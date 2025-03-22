#ifndef SCENE_H
#define SCENE_H

#include "addons.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void draw_sidebar(SDL_Window* window, SDL_Renderer* renderer);

void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b);

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path);

void load_icons(SDL_Renderer* renderer, Icon icons[], int NUM_ICONS);

#endif