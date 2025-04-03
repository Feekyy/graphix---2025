#ifndef DRAW_H
#define DRAW_H

#include "addons.h"

RGBColor handle_color_wheel_click(Point click, int window_width, int window_height);

void draw_line(SDL_Renderer* renderer, Line line, int winWidth, int winHeight);

void draw_square(SDL_Renderer* renderer, Square square, int winWidth, int winHeight);

#endif