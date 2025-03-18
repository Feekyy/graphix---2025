#ifndef DRAW_H
#define DRAW_H

#include "addons.h"

RGBColor handle_color_wheel_click(Point click, int window_width, int window_height);
void draw_line(Line line);

void draw_sqare(Point center, float side_length, RGBColor color);

#endif
