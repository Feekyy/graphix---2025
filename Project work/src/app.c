#include "app.h"
#include "scene.h"
#include "addons.h"
#include "draw.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_OBJECTS 5

Line objects[MAX_OBJECTS];
int object_count = 0;
int overwrite = 0;

int winWidth = 800;
int winHeight = 600;
const float SIDEBAR_WIDTH = 0.34f;

Point CurrentClick = {-1, -1};
Point start_point = {-1, -1};
Point end_point = {-1, -1}; 
bool drawing = false;

RGBColor CurrentColor = {255, 255, 255};

ShapeType currentShape = SHAPE_LINE;

int initialize_app(SDL_Window** window, SDL_GLContext* gl_context)
{
    int error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) 
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }

    *window = SDL_CreateWindow
    (
        "Peint from Temu",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        winWidth, winHeight,
        SDL_WINDOW_OPENGL
    );

    *gl_context = SDL_GL_CreateContext(*window);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

void run_app(SDL_Window* window)
{
    bool need_run = true;

    SDL_Event event;
    while (need_run) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    need_run = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        CurrentClick.x = event.button.x;
                        CurrentClick.y = event.button.y;

                        float click_x = (2.0f * CurrentClick.x) / winWidth - 1.0f;

                        if (click_x > -1.0f + SIDEBAR_WIDTH)
                        {
                            if (!drawing)
                            {
                                start_point.x = click_x;
                                start_point.y = 1.0f - (2.0f * CurrentClick.y) / winHeight;
                                drawing = true;
                            }
                            else
                            {
                                end_point.x = click_x;
                                end_point.y = 1.0f - (2.0f * CurrentClick.y) / winHeight;
                                drawing = false;
                                draw_line(start_point, end_point, CurrentColor);

                                if (object_count < MAX_OBJECTS) 
                                {
                                    objects[object_count].start = start_point;
                                    objects[object_count].end = end_point;
                                    objects[object_count].color = CurrentColor;
                                    object_count++;
                                    overwrite = 0;
                                }
                                else
                                {
                                    objects[overwrite].start = start_point;
                                    objects[overwrite].end = end_point;
                                    objects[overwrite].color = CurrentColor;
                                    if (overwrite != MAX_OBJECTS - 1) overwrite++;
                                    else overwrite = 0;
                                }
                            }
                        }
                        else
                        {
                            CurrentColor = handle_color_wheel_click(CurrentClick, winWidth, winHeight);
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_z && SDL_GetModState() & KMOD_CTRL)
                    {
                        if (object_count > 0) 
                        {
                            object_count--;
                        }
                    }
                    break;
                
            }
        }

        for (int i = 0; i < object_count; i++) 
        {
            draw_line(objects[i].start, objects[i].end, objects[i].color);
        }

        if (drawing && start_point.x != -1 && start_point.y != -1)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            Point current_point = {x / (float)800 * 2 - 1, 1 - y / (float)600 * 2};
            draw_line(start_point, current_point, CurrentColor);
        }

        draw_sidebar();

        SDL_GL_SwapWindow(window);
    }
}


void cleanup_app(SDL_Window* window, SDL_GLContext gl_context)
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}