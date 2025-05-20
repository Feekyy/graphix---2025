#ifndef DRAW_H
#define DRAW_H

#include "addons.h"
#include "scene.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

RGBColor handle_color_wheel_click(Point click, int window_width, int window_height);

void draw_sphere(float radius, RGBColor color);

void draw_cube(float size, RGBColor color);

void draw_color_wheel(int x, int y, int radius, RGBColor* current_color);

void handle_mouse_click(Scene* scene, Camera* camera, int x, int y, int winWidth, int winHeight);

void draw_sidebar(int window_width, int window_height, Scene *scene);

void draw_origin();

#endif