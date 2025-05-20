#include "scene.h"
#include "draw.h"
#include "addons.h"

#include <math.h>
#include <stdio.h>
#include <GL/glu.h>
#include <SDL2/SDL_image.h>

void init_scene(Scene* scene)
{
    scene->obj_list = create_obj_list();
    load_shape_icons(scene);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuse_light[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specular_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = 
    {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = 
    {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = 
    {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();

    draw_origin();

    ObjNode* current = scene->obj_list->head;
    while (current != NULL) 
    {
        glPushMatrix();
        glTranslatef(current->object.position.x, current->object.position.y, current->object.position.z);

        if (current->object.shape == SHAPE_CUBE)
        {
            draw_cube(current->object.size, current->object.color);
        } 
        else if (current->object.shape == SHAPE_SPHERE) 
        {
            draw_sphere(current->object.size, current->object.color);
        }

        glPopMatrix();
        current = current->next;
    }
}

void hsv_to_rgb(float h, float s, float v, float* r, float* g, float* b)
{
    int i;
    float f, p, q, t;

    if (s == 0) 
    {
        *r = *g = *b = v;
        return;
    }

    h *= 6;
    i = floor(h);
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));

    switch (i % 6) 
    {
        case 0: *r = v, *g = t, *b = p; break;
        case 1: *r = q, *g = v, *b = p; break;
        case 2: *r = p, *g = v, *b = t; break;
        case 3: *r = p, *g = q, *b = v; break;
        case 4: *r = t, *g = p, *b = v; break;
        case 5: *r = v, *g = p, *b = q; break;
    }
}

void load_shape_icons(Scene* scene)
{
    const char* icon_files[] = {"assets/cube_icon.png", "assets/sphere_icon.png"};
    int icon_positions[][2] = {{20, 180}, {20, 240}};

    for (int i = 0; i < NUM_ICONS; i++) 
    {
        SDL_Surface* surface = IMG_Load(icon_files[i]);
        if (!surface) {
            printf("Failed to load icon: %s\n", icon_files[i]);
            continue;
        }

        glGenTextures(1, &scene->shape_icons[i].texture_id);
        glBindTexture(GL_TEXTURE_2D, scene->shape_icons[i].texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        scene->shape_icons[i].x = icon_positions[i][0];
        scene->shape_icons[i].y = icon_positions[i][1];
        scene->shape_icons[i].width = surface->w;
        scene->shape_icons[i].height = surface->h;

        SDL_FreeSurface(surface);
    }
}