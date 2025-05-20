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

// Function to initialize the GUI components and resources
void init_gui(SDL_Renderer* renderer, int window_width, int window_height);

// Function to render the GUI components and handle user input
void render_gui(struct App* app, SDL_Renderer* renderer);

// Function to cleanup the GUI components and resources
GuiAction handle_gui_event(SDL_Event* event);

// Function to load GUI textures from image files
void cleanup_gui();

#endif