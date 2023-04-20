#include "circle.h"
#include <SDL2/SDL.h>
#include <math.h>

void set_circle_data(Circle* circle, double x, double y, double radius)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
}

double calc_circle_area(const Circle* circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
}

void draw_circle(Circle* circle, double points, SDL_Renderer* renderer)
{
	double degree = 360/points;
	int k = 1;
	int pointX1 = circle->x;
	int pointY1 = circle->y + circle->radius;
	int pointX2;
	int pointY2;
	//while (degree < 360)
//{
//switch ((int)degree)
	//	{
			//case (int)degree<=90:
			pointX2 = pointX1 + sin(degree);
			pointY2 = pointY1 + circle->radius;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, pointX1, pointY1, pointX2, pointY2);
	//		break;
	//	}
//	}
}
