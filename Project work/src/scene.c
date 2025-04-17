#include "scene.h"
#include "draw.h"
#include "addons.h"

#include <math.h>
#include <GL/glu.h>

#define MAX_OBJECTS 5

void init_scene(Scene* scene)
{
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
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
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

    h /= 60;
    i = floor(h);
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));

    switch (i) {
        case 0:
            *r = v; *g = t; *b = p;
            break;
        case 1:
            *r = q; *g = v; *b = p;
            break;
        case 2:
            *r = p; *g = v; *b = t;
            break;
        case 3:
            *r = p; *g = q; *b = v;
            break;
        case 4:
            *r = t; *g = p; *b = v;
            break;
        default:
            *r = v; *g = p; *b = q;
            break;
    }
}

void draw_origin()
{
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
}

void draw_sidebar(int window_width, int window_height, Scene *scene) 
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3ub(40, 40, 40);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(150, 0);
    glVertex2i(150, window_height);
    glVertex2i(0, window_height);
    glEnd();

    glColor3ub(scene->current_shape == SHAPE_CUBE ? 100 : 200, 200, 200);
    glBegin(GL_QUADS);
    glVertex2i(20, window_height - 60);
    glVertex2i(130, window_height - 60);
    glVertex2i(130, window_height - 100);
    glVertex2i(20, window_height - 100);
    glEnd();

    glColor3ub(scene->current_shape == SHAPE_SPHERE ? 100 : 200, 200, 200);
    glBegin(GL_QUADS);
    glVertex2i(20, window_height - 120);
    glVertex2i(130, window_height - 120);
    glVertex2i(130, window_height - 160);
    glVertex2i(20, window_height - 160);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
