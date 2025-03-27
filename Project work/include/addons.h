#ifndef ADDONS_H
#define ADDONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum 
{
    SHAPE_LINE,
    SHAPE_SQUARE
} ShapeType;

typedef struct Icon
{
    SDL_Texture* texture;
    SDL_Rect rect;
    ShapeType shape;
} Icon;

typedef struct RGBColor 
{
    unsigned char red, green, blue;
} RGBColor;

typedef struct Point 
{
    float x;
    float y;
} Point;

typedef struct Line 
{
    Point start;
    Point end;
    RGBColor color;
} Line;

typedef struct Square
{
    Point top_left;
    float width;
    float height;
    RGBColor color;
} Square;

typedef union Shapes
{
    Line line;
    Square square;
} Shapes;

#endif