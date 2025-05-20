#ifndef APP_H
#define APP_H

#include "camera.h"
#include "scene.h"
#include "gui.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

#define MAX_UNDO 50
#define SAVE_FILENAME "save/scene.sav"

typedef enum 
{
    APP_STATE_MENU,
    APP_STATE_3D_SCENE
} AppState;

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;
    Camera camera;
    Scene scene;
    Object3D undo_stack[MAX_UNDO];
    int undo_count;
    int window_width;
    int window_height;
    SDL_Renderer* renderer;
    AppState state;
} App;

// Function to initialize the application state and resources. 
void init_app(App* app, int width, int height);

// Function to initialize OpenGL context and set up viewport.
void init_opengl();

// Function to handle window resizing.
void reshape(GLsizei width, GLsizei height);

// Function to handle application events. 
void handle_app_events(App* app);

// Function to update the application state.
void update_app(App* app);

// Function to render the application state.
void render_app(App* app);

// Function to destroy the application state and resources.
void destroy_app(App* app);

// Function to undo the last object added to the scene.
void undo_last_object(App* app);

// Function to save the current scene to a file.
void save_scene(App* app);

// Function to load a scene from a file.
void load_scene(App* app);

// Function to clear the current scene.
void clear_scene(App* app);

#endif
