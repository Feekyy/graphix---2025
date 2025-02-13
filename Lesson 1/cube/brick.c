#include "brick.h"
#include <stdio.h>

void set_size(Brick* brick, double x, double y, double z)
{
    brick->x = x;
    brick->y = y;
    brick->z = z;
}

double calc_volume(const Brick* brick)
{
    return (brick->x*(brick->y*brick->z));
}

double calc_surface(const Brick* brick)
{
    return(2*(brick->x*brick->y)+(brick->x*brick->z)+(brick->y*brick->z));
}

void has_tet(const Brick* brick)
{
    if (brick->x == brick->y || brick->x == brick->z || brick->y == brick->z)
    {
        printf("One side of the rectangle is squared!");
    }
    else
    {
        printf("None side of the rectangle is square!");
    }
}