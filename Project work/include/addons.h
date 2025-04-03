#ifndef ADDONS_H
#define ADDONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum 
{
    SHAPE_PIPE,
    SHAPE_CUBE
} ShapeType;

typedef struct RGBColor 
{
    unsigned char red, green, blue;
} RGBColor;

typedef struct Point 
{
    float x;
    float y;
} Point;

typedef struct Pipe 
{
    Point start;
    Point end;
    RGBColor color;
} Pipe;

typedef struct Cube
{
    Point top_left;
    float width;
    float height;
    RGBColor color;
} Cube;

typedef union Shapes
{
    Pipe pipe;
    Cube cube;
} Shapes;

#endif