#include "brick.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Brick brick;
	double volume;
	double surface;
	
	set_size(&brick, 5, 8, 8);
	volume = calc_volume(&brick);
	surface = calc_surface(&brick);
	
	printf("Brick's volume: %lf\nCube's surface: %lf\n", volume, surface);
	has_tet(&brick);
	
	return 0;
}
