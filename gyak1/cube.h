#ifndef CUBE_H
#define CUBE_H

typedef struct Cube
{
	double x;
	double y;
	double z;
} Cube;

void set_size(Cube* cube, double x, double y, double z);

double calc_volume(const Cube* cube);

double calc_surface(const Cube* cube);

void has_tet(const Cube* cube);

#endif