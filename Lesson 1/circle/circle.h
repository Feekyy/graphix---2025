#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct Circle
{
	double x;
	double y;
	double radius;
} Circle;

void set_circle_data(Circle* circle, double x, double y, double radius);

double calc_circle_area(const Circle* circle);

#endif
