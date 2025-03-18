#include "scene.h"
#include "addons.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <SDL2/SDL_image.h>
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

void draw_sidebar()
{
    float sidebar_width = 0.34f;
    float wheel_radius = 0.15f;
    float wheel_center_x = -1.0f + wheel_radius + 0.02f;
    float wheel_center_y = 1.0f - wheel_radius - 0.02f;
    int segments = 360;

    glColor3f(white.red / 255.0f, white.green / 255.0f, white.blue / 255.0f);
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
        glVertex2f
        (
            wheel_center_x + wheel_radius * cosf(angle + M_PI),
            wheel_center_y + wheel_radius * sinf(angle + M_PI)
        );
    }
    glEnd();

    draw_sidebar_images(renderer, image1_texture, image2_texture);
}

SDL_Texture* load_texture(const char* path, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) 
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) 
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }
    
    SDL_FreeSurface(surface);
    return texture;
}

void draw_texture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int width, int height)
{
    SDL_Rect dest = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void draw_sidebar_images(SDL_Renderer* renderer, SDL_Texture* image1, SDL_Texture* image2)
{
    int sidebar_width = 0.34f * 800;
    int image_width = sidebar_width - 20;
    int image_height = image_width;
    int y_offset = 400;

    draw_texture(image1, renderer, 10, y_offset, image_width, image_height);
    draw_texture(image2, renderer, 10, y_offset + image_height + 10, image_width, image_height);
}