#include "draw.h"
#include "addons.h"
#include "scene.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <math.h>

RGBColor handle_color_wheel_click(Point click, int window_width, int window_height) 
{
    RGBColor selected_color = {0, 0, 0};

    float sidebar_width = 0.34f;
    float wheel_radius = 0.15f;
    float wheel_center_x = -1.0f + wheel_radius + 0.02f;
    float wheel_center_y = 1.0f - wheel_radius - 0.02f;

    float x = (2.0f * click.x) / window_width - 1.0f;
    float y = 1.0f - (2.0f * click.y) / window_height;

    float dx = x - wheel_center_x;
    float dy = y - wheel_center_y;
    float distance = sqrt(dx*dx + dy*dy);

    if (distance <= wheel_radius) 
    {
        float angle = atan2(dy, dx);
        angle = fmod(-angle + M_PI / 2, 2 * M_PI);
        if (angle < 0) angle += 2 * M_PI;
        
        float hue = angle * 180.0f / M_PI;
        float saturation = distance / wheel_radius;

        float r, g, b;
        hsv_to_rgb(hue, saturation, 1.0f, &r, &g, &b);

        selected_color.red = (unsigned char)(r * 255.0f);
        selected_color.green = (unsigned char)(g * 255.0f);
        selected_color.blue = (unsigned char)(b * 255.0f);
    }

    return selected_color;
}

void draw_line(Line line)
{
    glBegin(GL_LINES);
    glColor3ub(line.color.red, line.color.green, line.color.blue);
    glVertex2f(line.start.x, line.start.y);
    glVertex2f(line.end.x, line.end.y);
    glEnd();
}

void draw_square(Square square)
{
    glBegin(GL_QUADS);
    glColor3ub(square.color.red, square.color.green, square.color.blue);
    glVertex2f(square.top_left.x, square.top_left.y);
    glVertex2f(square.top_left.x + square.width, square.top_left.y);
    glVertex2f(square.top_left.x + square.width, square.top_left.y + square.height);
    glVertex2f(square.top_left.x, square.top_left.y + square.height);
    glEnd();
}