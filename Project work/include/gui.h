#ifndef GUI_H
#define GUI_H

#include "app.h"

#include <SDL2/SDL.h>

struct App;

typedef enum 
{
    GUI_NONE,
    GUI_NEW_WORLD,
    GUI_LOAD_WORLD,
    GUI_HELP,
    GUI_EXIT
} GuiAction;

void init_gui(SDL_Renderer* renderer, int window_width, int window_height);

void render_gui(struct App* app, SDL_Renderer* renderer);

GuiAction handle_gui_event(SDL_Event* event);

void cleanup_gui();

#endif