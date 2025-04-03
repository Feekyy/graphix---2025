#include "scene.h"
#include "addons.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
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

void draw_sidebar(SDL_Renderer* renderer, int window_width, int window_height)
{
    int sidebar_width = (int)(0.2f * window_width);
    float wheel_radius = 0.1f * window_width;
    float wheel_center_x = sidebar_width / 2;
    float wheel_center_y = wheel_radius + 0.05f * window_height;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect sidebar_rect = {0, 0, sidebar_width, window_height};
    SDL_RenderFillRect(renderer, &sidebar_rect);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawLine(renderer, sidebar_width, 0, sidebar_width, window_height);

    for(int y = (int)(wheel_center_y - wheel_radius); y <= wheel_center_y + wheel_radius; y++)
    {
        for(int x = (int)(wheel_center_x - wheel_radius); x <= wheel_center_x + wheel_radius; x++)
        {
            float dx = x - wheel_center_x;
            float dy = y - wheel_center_y;
            float distance = sqrt(dx*dx + dy*dy);
            
            if(distance <= wheel_radius)
            {
                float angle = atan2(dy, dx);
                if(angle < 0) angle += 2 * M_PI;
                
                float hue = angle / (2 * M_PI) * 360.0f;
                float saturation = distance / wheel_radius;
                
                float r, g, b;
                hsv_to_rgb(hue, saturation, 1.0f, &r, &g, &b);
                
                SDL_SetRenderDrawColor(renderer, (Uint8)(r * 255), (Uint8)(g * 255), (Uint8)(b * 255), 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path)
{
    SDL_Surface* surface = IMG_Load(file_path);
    if (surface == NULL) 
    {
        printf("Error loading texture: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_PixelFormat* format = surface->format;
    Uint32* pixels = (Uint32*)surface->pixels;
    Uint32 pixel = pixels[0];
    Uint8 r, g, b, s;
    SDL_GetRGBA(pixel, format, &r, &g, &b, &s);

    printf("Loaded texture. First pixel RGB: (%d, %d, %d, %d)\n", r, g, b, s);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void load_icons(SDL_Renderer* renderer, Icon icons[], int NUM_ICONS)
{
    const char* icon_files[] = {"assets/paint_line.jpg", "assets/paint_square.jpg"};
    ShapeType shapes[] = {SHAPE_LINE, SHAPE_SQUARE};

    for (int i = 0; i < NUM_ICONS; i++)
    {
        icons[i].texture = load_texture(renderer, icon_files[i]);
        icons[i].rect.x = 30;
        icons[i].rect.y = 300 + i * 110;
        icons[i].rect.w = 100;
        icons[i].rect.h = 100;
        icons[i].shape = shapes[i];

        if (icons[i].texture == NULL)
        {
            printf("Failed to load texture: %s\n", SDL_GetError());
        }
    }
}
