#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct RGB
{
	float red;
	float green;
	float blue;
} RGB;

typedef struct Circle
{
	double x;
	double y;
	double radius;
	RGB color;
} Circle;

void set_circle_data(Circle* circle, double x, double y, double radius);

double calc_circle_area(const Circle* circle);

#endif
