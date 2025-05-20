#include "gui.h"
#include "app.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>

#define BUTTON_COUNT 4
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_MARGIN 10

typedef struct 
{
    SDL_Rect rect;
    GLuint texture;
    const char* label;
} Button;

static Button buttons[BUTTON_COUNT];

void init_gui(SDL_Renderer* renderer, int window_width, int window_height) 
{
    int start_y = (window_height - (BUTTON_COUNT * (BUTTON_HEIGHT + BUTTON_MARGIN))) / 2;
    const char* labels[] = { "New World", "Load World", "Help", "Exit" };
    const char* image_files[] = { "assets/new.png", "assets/load.png", "assets/help.png", "assets/exit.png" };

    for (int i = 0; i < BUTTON_COUNT; i++) 
    {
        buttons[i].rect.x = (window_width - BUTTON_WIDTH) / 2;
        buttons[i].rect.y = start_y + i * (BUTTON_HEIGHT + BUTTON_MARGIN);
        buttons[i].rect.w = BUTTON_WIDTH;
        buttons[i].rect.h = BUTTON_HEIGHT;
        buttons[i].label = labels[i];

        SDL_Surface* surface = IMG_Load(image_files[i]);
        if (!surface) 
        {
            printf("Failed to load image: %s\n", image_files[i]);
            continue;
        }

        glGenTextures(1, &buttons[i].texture);
        glBindTexture(GL_TEXTURE_2D, buttons[i].texture);
        
        int mode = GL_RGB;
        if(surface->format->BytesPerPixel == 4) 
        {
            mode = GL_RGBA;
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SDL_FreeSurface(surface);

        if (!buttons[i].texture) 
        {
            printf("Failed to create texture from %s\n", image_files[i]);
        }
    }
}

void render_gui(struct App* app, SDL_Renderer* renderer) 
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, app->window_width, app->window_height, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < BUTTON_COUNT; i++) 
    {
        glBindTexture(GL_TEXTURE_2D, buttons[i].texture);
        
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(buttons[i].rect.x, buttons[i].rect.y);
        glTexCoord2f(1, 0); glVertex2f(buttons[i].rect.x + buttons[i].rect.w, buttons[i].rect.y);
        glTexCoord2f(1, 1); glVertex2f(buttons[i].rect.x + buttons[i].rect.w, buttons[i].rect.y + buttons[i].rect.h);
        glTexCoord2f(0, 1); glVertex2f(buttons[i].rect.x, buttons[i].rect.y + buttons[i].rect.h);
        glEnd();
    }

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

GuiAction handle_gui_event(SDL_Event* event) 
{
    if (event->type == SDL_MOUSEBUTTONDOWN) 
    {
        int x = event->button.x;
        int y = event->button.y;

        for (int i = 0; i < BUTTON_COUNT; i++) 
        {
            if (x >= buttons[i].rect.x && x <= buttons[i].rect.x + buttons[i].rect.w && y >= buttons[i].rect.y && y <= buttons[i].rect.y + buttons[i].rect.h) 
            {
                return (GuiAction)(i + 1);
            }
        }
    }

    return GUI_NONE;
}

void cleanup_gui() 
{
    for (int i = 0; i < BUTTON_COUNT; i++) 
    {
        if (buttons[i].texture) 
        {
            glDeleteTextures(1, &buttons[i].texture);
            buttons[i].texture = 0;
        }
    }
}