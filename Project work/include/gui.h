#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

typedef enum 
{
    GUI_NONE,
    GUI_NEW_WORLD,
    GUI_LOAD_WORLD,
    GUI_HELP,
    GUI_EXIT
} GuiAction;

void init_gui(SDL_Renderer* renderer);

void render_gui(SDL_Renderer* renderer);

GuiAction handle_gui_event(SDL_Event* event);

void cleanup_gui();

#endif