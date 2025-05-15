#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "addons.h"
#include "objlist.h"
#include <GL/gl.h>

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


void init_scene(Scene* scene);
void set_lighting();
void set_material(const Material* material);
void update_scene(Scene* scene);
void render_scene(const Scene* scene);
void show_texture_preview();
void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b);
void load_shape_icons(Scene* scene);

#endif
