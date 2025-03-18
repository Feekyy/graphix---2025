#include "app.h"
#include "scene.h"
#include "addons.h"
#include "draw.h"
#include "objlist.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_OBJECTS 5

SDL_Texture* line_icon = NULL;
SDL_Texture* square_icon = NULL;

ObjList* obj_list;
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

ShapeType currentShape = SHAPE_SQUARE;

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

    obj_list = create_obj_list();

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) 
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    line_icon = load_texture("paint_line.png", *renderer);
    square_icon = load_texture("paint_square.png", *renderer);

    if (image1_texture == NULL || image2_texture == NULL) 
    {
        return -1;
    }

    return 0;
}

void run_app(SDL_Window* window)
{
    bool need_run = true;

    SDL_Event event;
    while (need_run) 
    {
        Line temp_line;
        Square temp_square;

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

        draw_sidebar(renderer, line_icon, square_icon);

        SDL_GL_SwapWindow(window);
    }
}


void cleanup_app(SDL_Window* window, SDL_GLContext gl_context)
{
    SDL_DestroyTexture(line_icon);
    SDL_DestroyTexture(square_icon);
    SDL_DestroyRenderer(renderer);
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}