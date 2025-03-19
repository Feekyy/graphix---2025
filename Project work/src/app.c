#include "app.h"
#include "addons.h"
#include "draw.h"
#include "scene.h"
#include "objlist.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <stdbool.h>

#define MAX_OBJECTS 5
#define SIDEBAR_WIDTH 0.34f

int winWidth = 800;
int winHeight = 600;

Point CurrentClick = {0, 0};
RGBColor CurrentColor = {255, 0, 0};
ShapeType currentShape = SHAPE_SQUARE;
bool drawing = false;
Point start_point, end_point;

ObjList* obj_list;
int overwrite = 0;

int initialize_app(SDL_Window** window, SDL_GLContext* gl_context, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    *window = SDL_CreateWindow("Drawing App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (*window == NULL) 
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    *gl_context = SDL_GL_CreateContext(*window);
    if (*gl_context == NULL) 
    {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) 
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_GL_DeleteContext(*gl_context);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }

    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    return 0;
}

void run_app(SDL_Window* window, SDL_Renderer* renderer)
{
    printf("Entering run_app\n");

    bool need_run = true;

    obj_list = create_obj_list();
    if (obj_list == NULL) 
    {
        printf("Failed to create object list\n");
        return;
    }

    SDL_Event event;
    while (need_run) 
    {
        Line temp_line;
        Square temp_square;

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_sidebar(window, renderer);

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
                            switch (currentShape)
                            {
                                case SHAPE_LINE:
                                    temp_line.color = CurrentColor;
                                    if (!drawing)
                                    {
                                        start_point.x = click_x;
                                        start_point.y = 1.0f - (2.0f * CurrentClick.y) / winHeight;
                                        temp_line.start = start_point;
                                        drawing = true;
                                    }
                                    else
                                    {
                                        end_point.x = click_x;
                                        end_point.y = 1.0f - (2.0f * CurrentClick.y) / winHeight;
                                        temp_line.end = end_point;
                                        drawing = false;
                                        draw_line(temp_line);

                                        if (obj_list->count < MAX_OBJECTS) 
                                        {
                                            Shapes new_shape;
                                            new_shape.line = temp_line;
                                            add_object(obj_list, new_shape);
                                            overwrite = 0;
                                        }
                                        else
                                        {
                                            Shapes new_shape;
                                            new_shape.line = temp_line;
                                            switch_shapes(obj_list, new_shape, overwrite);
                                            if (overwrite != MAX_OBJECTS - 1) overwrite++;
                                            else overwrite = 0;
                                        }
                                    }
                                    break;
                                case SHAPE_SQUARE:
                                    temp_square.color = CurrentColor;
                                    if (!drawing)
                                    {
                                        temp_square.top_left.x = click_x;
                                        temp_square.top_left.y = 1.0f - (2.0f * CurrentClick.y) / winHeight;
                                        drawing = true;
                                    }
                                    else
                                    {
                                        end_point.x = click_x;
                                        end_point.y = 1.0f - (2.0f * CurrentClick.y) / winHeight;
                                        temp_square.width = end_point.x - temp_square.top_left.x;
                                        temp_square.height = end_point.y - temp_square.top_left.y;
                                        drawing = false;
                                        draw_square(temp_square);
                                
                                        if (obj_list->count < MAX_OBJECTS) 
                                        {
                                            Shapes new_shape;
                                            new_shape.square = temp_square;
                                            add_object(obj_list, new_shape);
                                            overwrite = 0;
                                        }
                                        else
                                        {
                                            Shapes new_shape;
                                            new_shape.square = temp_square;
                                            switch_shapes(obj_list, new_shape, overwrite);
                                            if (overwrite != MAX_OBJECTS - 1) overwrite++;
                                            else overwrite = 0;
                                        }
                                    }
                                    break;
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
                        if (obj_list->count > 0) 
                        {
                            delete_last_object(obj_list);
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (drawing)
                    {
                        float mouse_x = (2.0f * event.motion.x) / winWidth - 1.0f;
                        float mouse_y = 1.0f - (2.0f * event.motion.y) / winHeight;
                        switch(currentShape)
                        {
                            case SHAPE_LINE:
                                temp_line.end.x = mouse_x;
                                temp_line.end.y = mouse_y;
                                break;
                            case SHAPE_SQUARE:
                                temp_square.width = mouse_x - temp_square.top_left.x;
                                temp_square.height = mouse_y - temp_square.top_left.y;
                                break;
                        }
                    }
                    break;               
            }
        }

        ObjNode* currentNode = obj_list->head;
        while (currentNode != NULL)
        {
            switch(currentShape)
            {
                case SHAPE_LINE:
                    draw_line(currentNode->shape.line);
                    break;
                case SHAPE_SQUARE:
                    draw_square(currentNode->shape.square);
                    break;
            }
            currentNode = currentNode->next;
        }

        if (drawing)
        {
            switch(currentShape)
            {
                case SHAPE_LINE:
                    draw_line(temp_line);
                    break;
                case SHAPE_SQUARE:
                    draw_square(temp_square);
                    break;
            }
        }
        
        SDL_GL_SwapWindow(window);
    }
}

void cleanup_app(SDL_Window* window, SDL_GLContext gl_context, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}