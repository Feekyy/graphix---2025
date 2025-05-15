#include "draw.h"
#include "addons.h"
#include "scene.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <math.h>

#define MAX_OBJECTS 5

RGBColor handle_color_wheel_click(Point click, int window_width, int window_height) 
{
    RGBColor selected_color = {0, 0, 0};

    float wheel_radius = 70.0f;
    float wheel_center_x = 75.0f;
    float wheel_center_y = window_height - 75.0f;

    float x = click.x - wheel_center_x;
    float y = (window_height - click.y) - wheel_center_y;

    float distance = sqrt(x*x + y*y);

    if (distance <= wheel_radius) 
    {
        float angle = atan2(y, x);
        if (angle < 0) angle += 2 * M_PI;
        
        float hue = angle / (2 * M_PI);
        float saturation = distance / wheel_radius;
        float value = 1.0f;

        float r, g, b;
        hsv_to_rgb(hue, saturation, value, &r, &g, &b);

        selected_color.red = (unsigned char)(r * 255.0f);
        selected_color.green = (unsigned char)(g * 255.0f);
        selected_color.blue = (unsigned char)(b * 255.0f);
    }

    return selected_color;
}

void handle_sidebar_click(int x, int y, int window_width, int window_height, Scene *scene) 
{
    const int sidebar_width = 150;
    const int icon_padding = 10;
    const int icon_size = sidebar_width - 2 * icon_padding;
    const int icons_start_y = window_height - 180;

    for (int i = 0; i < NUM_ICONS; i++) 
    {
        int icon_x = icon_padding;
        int icon_y = icons_start_y - i * (icon_size + icon_padding);
        
        if (x >= icon_x && x <= icon_x + icon_size &&
            y >= window_height - icon_y && y <= window_height - (icon_y - icon_size)) 
        {
            scene->current_shape = i;
            printf("Selected shape: %d\n", i);
            return;
        }
    }

    if (x < sidebar_width) 
    {
        RGBColor new_color = handle_color_wheel_click((Point){x, y}, window_width, window_height);
        if (new_color.red != 0 || new_color.green != 0 || new_color.blue != 0) 
        {
            scene->current_color = new_color;
            printf("Selected color: (%d, %d, %d)\n", new_color.red, new_color.green, new_color.blue);
        }
    }
}

void draw_color_wheel(int x, int y, int radius, RGBColor* current_color)
{
    int i, j;
    float r, g, b;
    float angle, distance;

    glBegin(GL_POINTS);
    for (i = -radius; i <= radius; i++) 
    {
        for (j = -radius; j <= radius; j++) 
        {
            distance = sqrt(i*i + j*j);
            if (distance <= radius) {
                angle = atan2(j, i);
                if (angle < 0) angle += 2 * M_PI;
                
                float h = angle / (2 * M_PI);
                float s = distance / radius;
                float v = 1.0f;
                
                hsv_to_rgb(h, s, v, &r, &g, &b);
                glColor3f(r, g, b);
                glVertex2i(x + i, y + j);
            }
        }
    }
    glEnd();

    glColor3ub(255 - current_color->red, 255 - current_color->green, 255 - current_color->blue);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glPointSize(1.0f);
}

void draw_sphere(float radius, int slices, int stacks, RGBColor color)
{
    glColor3ub(color.red, color.green, color.blue);
    glPushMatrix();

    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_LINE);
    gluSphere(quadric, radius, slices, stacks);
    gluDeleteQuadric(quadric);

    glPopMatrix();
}

void draw_cube(float size, RGBColor color)
{
    glColor3ub(color.red, color.green, color.blue);
    glPushMatrix();
    glScalef(size, size, size);

    float half = size / 2.0f;
    glBegin(GL_QUADS);

    glVertex3f(-half, -half,  half);
    glVertex3f( half, -half,  half);
    glVertex3f( half,  half,  half);
    glVertex3f(-half,  half,  half);

    glVertex3f(-half, -half, -half);
    glVertex3f(-half,  half, -half);
    glVertex3f( half,  half, -half);
    glVertex3f( half, -half, -half);

    glVertex3f(-half,  half, -half);
    glVertex3f(-half,  half,  half);
    glVertex3f( half,  half,  half);
    glVertex3f( half,  half, -half);

    glVertex3f(-half, -half, -half);
    glVertex3f( half, -half, -half);
    glVertex3f( half, -half,  half);
    glVertex3f(-half, -half,  half);

    glVertex3f( half, -half, -half);
    glVertex3f( half,  half, -half);
    glVertex3f( half,  half,  half);
    glVertex3f( half, -half,  half);

    glVertex3f(-half, -half, -half);
    glVertex3f(-half, -half,  half);
    glVertex3f(-half,  half,  half);
    glVertex3f(-half,  half, -half);
    glEnd();

    glPopMatrix();
}

void handle_mouse_click(Scene* scene, Camera* camera, int x, int y, int winWidth, int winHeight)
{
    if (x < 150) 
    {
        handle_sidebar_click(x, y, winWidth, winHeight, scene);
    } 
    else 
    {
        float ndc_x = (2.0f * x) / winWidth - 1.0f;
        float ndc_y = 1.0f - (2.0f * y) / winHeight;

        float placement_distance = 10.0f;

        float angle_horizontal = degree_to_radian(camera->rotation.z);
        float angle_vertical = degree_to_radian(camera->rotation.x);

        float world_x = camera->position.x + placement_distance * cos(angle_horizontal) * ndc_x;
        float world_y = camera->position.y + placement_distance * sin(angle_horizontal) * ndc_x;
        float world_z = camera->position.z + placement_distance * sin(angle_vertical) * ndc_y;

        Object3D new_object;
        new_object.position = (vec3){world_x, world_y, world_z};
        new_object.color = scene->current_color;
        new_object.shape = scene->current_shape;
        new_object.size = (scene->current_shape == SHAPE_SPHERE) ? 0.5f : 1.0f;

        add_object(scene->obj_list, new_object);

        printf("Added new object: Position (%.2f, %.2f, %.2f), Shape: %d, Color: (%d, %d, %d)\n", world_x, world_y, world_z, new_object.shape, new_object.color.red, new_object.color.green, new_object.color.blue);
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
    const int sidebar_width = 150;
    const int icon_padding = 10;
    const int icon_size = sidebar_width - 2 * icon_padding;
    const int icons_start_y = window_height - 180;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    draw_color_wheel(sidebar_width / 2, window_height - 75, 70, &scene->current_color);

    for (int i = 0; i < NUM_ICONS; i++) 
    {
        Icon* icon = &scene->shape_icons[i];
        int icon_x = icon_padding;
        int icon_y = icons_start_y - i * (icon_size + icon_padding);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, icon->texture_id);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2i(icon_x, icon_y);
        glTexCoord2f(1, 0); glVertex2i(icon_x + icon_size, icon_y);
        glTexCoord2f(1, 1); glVertex2i(icon_x + icon_size, icon_y - icon_size);
        glTexCoord2f(0, 1); glVertex2i(icon_x, icon_y - icon_size);
        glEnd();
        
        glDisable(GL_TEXTURE_2D);

        if (scene->current_shape == i) 
        {
            glColor3f(1.0f, 1.0f, 0.0f);
            glLineWidth(2.0f);
            glBegin(GL_LINE_LOOP);
            glVertex2i(icon_x - 2, icon_y + 2);
            glVertex2i(icon_x + icon_size + 2, icon_y + 2);
            glVertex2i(icon_x + icon_size + 2, icon_y - icon_size - 2);
            glVertex2i(icon_x - 2, icon_y - icon_size - 2);
            glEnd();
            glLineWidth(1.0f);
        }
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(sidebar_width, 0);
    glVertex2i(sidebar_width, window_height);
    glVertex2i(0, window_height);
    glEnd();

    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}