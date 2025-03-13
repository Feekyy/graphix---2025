#include "draw.h"
#include "addons.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

void draw_line(Point start, Point end, RGBColor color)
{
    glColor3ub(color.blue, color.green, color.red);
    glBegin(GL_LINES);
        glVertex2f(start.x, start.y);
        glVertex2f(end.x, end.y);
    glEnd();
}

void draw_sqare(Point center, float side_length, RGBColor color)
{
    glColor3ub(color.blue, color.green, color.red);
    glBegin(GL_QUADS);
        glVertex2f(center.x - side_length / 2.0f, center.y - side_length / 2.0f);
        glVertex2f(center.x + side_length / 2.0f, center.y - side_length / 2.0f);
        glVertex2f(center.x + side_length / 2.0f, center.y + side_length / 2.0f);
        glVertex2f(center.x - side_length / 2.0f, center.y + side_length / 2.0f);
    glEnd();
}