#include "app.h"
#include "scene.h"
#include "draw.h"
#include "gui.h"

#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->undo_count = 0;
    app->is_running = false;

    app->window_width = width;
    app->window_height = height;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) 
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow
    (
        "Unreel engine from temu!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL
    );
    if (app->window == NULL) 
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (app->renderer == NULL) 
    {
        printf("[ERROR] Unable to create renderer: %s\n", SDL_GetError());
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) 
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) 
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_gui(app->renderer);
    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) 
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else 
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_right_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) 
    {
        GuiAction action = handle_gui_event(&event);
        switch (action) 
        {
            case GUI_NEW_WORLD:
                printf("New World button clicked!\n");
                clear_scene(app);
                break;
            case GUI_LOAD_WORLD:
                printf("Load World button clicked!\n");
                load_scene(app);
                break;
            case GUI_HELP:
                printf("Help button clicked!\n");
                break;
            case GUI_EXIT:
                app->is_running = false;
                break;
            default:
                switch (event.type) 
                {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) 
                    {
                        case SDL_SCANCODE_W:
                            set_camera_speed(&(app->camera), 1);
                            break;
                        case SDL_SCANCODE_S:
                            set_camera_speed(&(app->camera), -1);
                            break;
                        case SDL_SCANCODE_A:
                            set_camera_side_speed(&(app->camera), 1);
                            break;
                        case SDL_SCANCODE_D:
                            set_camera_side_speed(&(app->camera), -1);
                            break;
                        case SDL_SCANCODE_SPACE:
                            set_camera_vertical_speed(&(app->camera), 1);
                            break;
                        case SDL_SCANCODE_LSHIFT:
                            set_camera_vertical_speed(&(app->camera), -1);
                            break;
                        case SDL_SCANCODE_Y:
                            undo_last_object(app);
                            break;
                        case SDL_SCANCODE_F1:
                            clear_scene(app);
                            break;
                        case SDL_SCANCODE_F5:
                            save_scene(app);
                            break;
                        case SDL_SCANCODE_F6:
                            load_scene(app);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) 
                    {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_S:
                            set_camera_speed(&(app->camera), 0);
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_D:
                            set_camera_side_speed(&(app->camera), 0);
                            break;
                        case SDL_SCANCODE_SPACE:
                        case SDL_SCANCODE_LSHIFT:
                            set_camera_vertical_speed(&(app->camera), 0);
                            break;
                    default:
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) 
                {
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);

                    int window_width, window_height;
                    SDL_GetWindowSize(app->window, &window_width, &window_height);

                    handle_mouse_click(&(app->scene), &(app->camera), mouse_x, mouse_y, window_width, window_height);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) 
                {
                    is_right_mouse_down = true;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                }
                break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x, &y);
                    if (is_right_mouse_down) 
                    {
                        rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
                        mouse_x = x;
                        mouse_y = y;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_RIGHT) 
                    {
                        is_right_mouse_down = false;
                    }
                    break;
                case SDL_QUIT:
                    app->is_running = false;
                    break;
                default:
                    break;
                }
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));

    if (app->scene.is_drawing) 
    {
        int window_width, window_height;
        SDL_GetWindowSize(app->window, &window_width, &window_height);

        if (app->scene.current_shape == SHAPE_SPHERE) 
        {
            draw_sphere(0.5f, 32, 32, app->scene.current_color);
        } 
        else if (app->scene.current_shape == SHAPE_CUBE) 
        {
            draw_cube(1.0f, app->scene.current_color);
        }
    }

    glPopMatrix();

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    render_gui(app->renderer);
    SDL_RenderPresent(app->renderer);

    SDL_GL_SwapWindow(app->window);

    if (app->camera.is_preview_visible) 
    {
        show_texture_preview();
    }

    int window_width, window_height;
    SDL_GetWindowSize(app->window, &window_width, &window_height);

    draw_sidebar(window_width, window_height, &(app->scene));

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    cleanup_gui();

    if (app->gl_context != NULL) 
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) 
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}

void undo_last_object(App* app)
{
    if (app->scene.obj_list->count > 0) 
    {
        if (app->undo_count < MAX_UNDO) 
        {
            ObjNode* last = app->scene.obj_list->head;
            while (last->next != NULL) 
            {
                last = last->next;
            }
            app->undo_stack[app->undo_count++] = last->object;
        }
        delete_last_object(app->scene.obj_list);
    }
}

void save_scene(App* app)
{
    FILE* file = fopen(SAVE_FILENAME, "wb");
    if (file == NULL) 
    {
        printf("Error opening file for saving.\n");
        return;
    }

    fwrite(&app->scene.obj_list->count, sizeof(int), 1, file);

    ObjNode* current = app->scene.obj_list->head;
    while (current != NULL) 
    {
        fwrite(&current->object, sizeof(Object3D), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Scene saved successfully.\n");
}

void load_scene(App* app)
{
    FILE* file = fopen(SAVE_FILENAME, "rb");
    if (file == NULL) 
    {
        printf("Error opening file for loading.\n");
        return;
    }

    int object_count;
    fread(&object_count, sizeof(int), 1, file);

    while (app->scene.obj_list->head != NULL) 
    {
        delete_last_object(app->scene.obj_list);
    }

    for (int i = 0; i < object_count; i++) 
    {
        Object3D obj;
        fread(&obj, sizeof(Object3D), 1, file);
        add_object(app->scene.obj_list, obj);
    }

    fclose(file);
    printf("Scene loaded successfully.\n");
}

void clear_scene(App* app)
{
    while (app->scene.obj_list->head != NULL) 
    {
        delete_last_object(app->scene.obj_list);
    }
    app->undo_count = 0;
    printf("Scene cleared.\n");
}