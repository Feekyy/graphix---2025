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
    Point position;
    Size size;
    ShapeType shape;
} Icon;

typedef struct Scene
{
    ObjList obj_list;
    GLuint texture_id;
    Icon icons[NUM_ICONS];
    float window_width;
    float window_height;
    Material material;
} Scene;


void init_scene(Scene* scene);
void set_lighting();
void set_material(const Material* material);
void update_scene(Scene* scene);
void render_scene(const Scene* scene);
void show_texture_preview();
void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b);

#endif
