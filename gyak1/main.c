#include "cube.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Cube cube;
	double volume;
	double surface;
	
	set_size(&cube, 5, 8, 8);
	volume = calc_volume(&cube);
	surface = calc_surface(&cube);
	
	printf("Cube's volume: %lf\nCube's surface: %lf\n", volume, surface);
	has_tet(&cube);
	
	return 0;
}
