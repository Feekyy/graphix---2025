#ifndef BRICK_H
#define BRICK_H

typedef struct Brick
{
	double x;
	double y;
	double z;
} Brick;

void set_size(Brick* brick, double x, double y, double z);

double calc_volume(const Brick* brick);

double calc_surface(const Brick* brick);

void has_tet(const Brick* brick);

#endif