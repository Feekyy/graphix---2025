#include "circle.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main(int argc, char* argv[])
{
	Circle circle;
	double area;
	GLfloat radius = 50.0f;
	GLfloat angle, x, y;

	int error_code;
	SDL_Window* window;
	bool need_run;
	SDL_Event event;
	SDL_GLContext gl_context;
	int i;
  
	error_code = SDL_Init(SDL_INIT_EVERYTHING);
	if (error_code != 0) 
	{
	  printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
	  return error_code;
	}
  
	window = SDL_CreateWindow
	(
	  "Main Window",
	  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	  800, 600,
	  SDL_WINDOW_OPENGL
	);

	gl_context = SDL_GL_CreateContext(window);
  	glClearColor(0, 0, 0, 1);
 	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(window);


	need_run = true;
	while (need_run) 
	{
		for (angle = 0.0f; angle <= (2.0f * M_PI); angle += 0.01f)
		{
			x = radius * sin(angle);
			y = radius * cos(angle);
			glVertex3f(x, y, 0.0f);
		}
		glEnd();
	}
	
	set_circle_data(&circle, 5, 10, 8);
	area = calc_circle_area(&circle);
	
	printf("Circle area: %lf\n", area);
	
	return 0;
}
