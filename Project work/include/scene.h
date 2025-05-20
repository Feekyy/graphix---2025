#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "addons.h"
#include "objlist.h"

#include <GL/gl.h>
#include <stdbool.h>

#define NUM_ICONS 2

typedef struct 
{
    GLuint texture_id;
    int x;
    int y;
    int width;
    int height;
} Icon;

typedef struct Scene
{
    RGBColor current_color;
    ShapeType current_shape;
    ObjList* obj_list;
    GLuint texture_id;
    Icon shape_icons[NUM_ICONS];
    float window_width;
    float window_height;
    Material material;
    int obj_count;
    bool is_drawing;
    Point first_click;
} Scene;

// Function to initialize the scene data structure and load shape icons.
void init_scene(Scene* scene);

// Function to set the lighting properties for the scene.
void set_lighting();

// Function to set the current material for the scene.
void set_material(const Material* material);

// Function to update the scene data structure based on user interactions.
void update_scene(Scene* scene);

// Function to render the scene using OpenGL.
void render_scene(const Scene* scene);

// Function to draw the origin in the scene.
void show_texture_preview();

// Function to convert HSV color values to RGB color values.
void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b);

// Function to load the shape icons for the scene.
void load_shape_icons(Scene* scene);

#endif
