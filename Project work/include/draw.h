#ifndef DRAW_H
#define DRAW_H

#include "addons.h"
#include "scene.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Function to handle color wheel click and return selected color.
RGBColor handle_color_wheel_click(Point click, int window_width, int window_height);

// Function to draw a sphere with given radius and color.
void draw_sphere(float radius, RGBColor color);

// Function to draw a cube with given size and color.
void draw_cube(float size, RGBColor color);

// Function to draw color wheel at given position and with given radius.
void draw_color_wheel(int x, int y, int radius, RGBColor* current_color);

// Function to draw scene using given camera and scene.
void handle_mouse_click(Scene* scene, Camera* camera, int x, int y, int winWidth, int winHeight);

// Function to draw sidebar for scene manipulation.
void draw_sidebar(int window_width, int window_height, Scene *scene);

// Function to draw texture preview in a separate window.
void draw_origin();

#endif