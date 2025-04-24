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

typedef enum 
{
    SHAPE_CUBE,
    SHAPE_SPHERE
} ShapeType;

typedef struct Point 
{
    float x;
    float y;
    float z;
} Point;

typedef struct Cube 
{
    Point center;
    float side_length;
    Material material;
} Cube;

typedef struct Sphere
{
    Point center;
    float radius;
    Material material;
} Sphere;

typedef union Shapes
{
    Cube cube;
    Sphere sphere;
} Shapes;

typedef struct Object3D
{
    vec3 position;
    RGBColor color;
    ShapeType shape;
    float size;
} Object3D;

double degree_to_radian(double degree);

#endif