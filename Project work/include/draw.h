#ifndef DRAW_H
#define DRAW_H

#include "addons.h"

RGBColor handle_color_wheel_click(Point click, int window_width, int window_height);

void draw_pipe(SDL_Renderer* renderer, Pipe pipe, int winWidth, int winHeight);

void draw_cube(SDL_Renderer* renderer, Cube cube, int winWidth, int winHeight);

#endif