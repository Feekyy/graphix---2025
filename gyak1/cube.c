#include "cube.h"
#include <stdio.h>

void set_size(Cube* cube, double x, double y, double z)
{
    cube->x = x;
    cube->y = y;
    cube->z = z;
}

double calc_volume(const Cube* cube)
{
    return (cube->x*(cube->y*cube->z));
}

double calc_surface(const Cube* cube)
{
    return(2*(cube->x*cube->y)+(cube->x*cube->z)+(cube->y*cube->z));
}

void has_tet(const Cube* cube)
{
    if (cube->x == cube->y || cube->x == cube->z || cube->y == cube->z)
    {
        printf("One side of a rectangle is a square!");
    }
    else
    {
        printf("None side of a rectangle is a square!");
    }
}