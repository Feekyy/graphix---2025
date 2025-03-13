#ifndef ADDONS_H
#define ADDONS_H

typedef enum 
{
    SHAPE_POINT,
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE,
    SHAPE_SQUARE
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

typedef struct ObjectList
{
    ShapeType shape_type;
    union 
    {
        Line line;
        Square square;
    };

    struct ObjectList* next;
}

#endif