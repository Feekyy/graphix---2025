#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

typedef struct Circle
{
	double x;
	double y;
	double radius;
} Circle;

void set_circle_data(Circle* circle, double x, double y, double radius);

void draw_circle(Circle* cirle, double points, SDL_Renderer* renderer);

double calc_circle_area(const Circle* circle);

#endif
