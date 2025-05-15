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
} App;

void init_app(App* app, int width, int height);

void init_opengl();

void reshape(GLsizei width, GLsizei height);

void handle_app_events(App* app);

void update_app(App* app);

void render_app(App* app);

void destroy_app(App* app);

void undo_last_object(App* app);

void save_scene(App* app);

void load_scene(App* app);

void clear_scene(App* app);

#endif
