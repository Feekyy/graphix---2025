#ifndef ADDONS_H
#define ADDONS_H

#include <GL/gl.h>

typedef struct RGBColor
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGBColor;

typedef struct Material
{
    struct 
    {
        float red;
        float green;
        float blue;
    } ambient;
    struct 
    {
        float red;
        float green;
        float blue;
    } diffuse;
    struct 
    {
        float red;
        float green;
        float blue;
    } specular;
    float shininess;
} Material;

typedef struct 
{
    float width;
    float height;
} Size;

typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

typedef enum 
{
    SHAPE_CUBE,
    SHAPE_SPHERE
} ShapeType;

typedef struct 
{
    vec3 position;
    RGBColor color;
    ShapeType shape;
} Object3D;

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

double degree_to_radian(double degree);

#endif