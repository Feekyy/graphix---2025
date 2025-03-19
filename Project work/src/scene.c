#include "scene.h"
#include "addons.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b)
{
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    if (h >= 0 && h < 60) 
    {
        *r = c; *g = x; *b = 0;
    } 
    else if (h >= 60 && h < 120) 
    {
        *r = x; *g = c; *b = 0;
    } 
    else if (h >= 120 && h < 180) 
    {
        *r = 0; *g = c; *b = x;
    } 
    else if (h >= 180 && h < 240) 
    {
        *r = 0; *g = x; *b = c;
    } 
    else if (h >= 240 && h < 300) 
    {
        *r = x; *g = 0; *b = c;
    } 
    else 
    {
        *r = c; *g = 0; *b = x;
    }

    *r += m; *g += m; *b += m;
}

RGBColor black = {0, 0, 0};
RGBColor white = {255, 255, 255};

void draw_color_wheel(float h, float s, float v, float* r, float* g, float* b) 
{
    hsv_to_rgb(h, s, v, r, g, b);
}

void draw_sidebar(SDL_Window* window, SDL_Renderer* renderer)
{
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    float sidebar_width = 0.34f;
    float wheel_radius = 0.15f;
    float wheel_center_x = -1.0f + wheel_radius + 0.02f;
    float wheel_center_y = 1.0f - wheel_radius - 0.02f;
    int segments = 360;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(-1.0f + sidebar_width, 1.0f);
        glVertex2f(-1.0f + sidebar_width, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(wheel_center_x, wheel_center_y);
    
    for(int i = 0; i <= segments; i++) 
    {
        float angle = 2.0f * M_PI * i / segments;
        float hue = 360.0f * i / segments;
        float r, g, b;
        hsv_to_rgb(hue, 1.0f, 1.0f, &r, &g, &b);
        
        glColor3f(r, g, b);
        glVertex2f(
            wheel_center_x + wheel_radius * cosf(angle),
            wheel_center_y + wheel_radius * sinf(angle)
        );
    }
    glEnd();

    glFlush();
}