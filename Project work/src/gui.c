#include "gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#define BUTTON_COUNT 4
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_MARGIN 10

typedef struct {
    SDL_Rect rect;
    const char* label;
} Button;

static Button buttons[BUTTON_COUNT];
static TTF_Font* font = NULL;

void init_gui(SDL_Renderer* renderer) 
{
    TTF_Init();
    font = TTF_OpenFont("assets/Arial.ttf", 24);

    int start_y = 50;
    const char* labels[] = { "New World", "Load World", "Help", "Exit" };

    for (int i = 0; i < BUTTON_COUNT; i++) 
    {
        buttons[i].rect.x = 50;
        buttons[i].rect.y = start_y + i * (BUTTON_HEIGHT + BUTTON_MARGIN);
        buttons[i].rect.w = BUTTON_WIDTH;
        buttons[i].rect.h = BUTTON_HEIGHT;
        buttons[i].label = labels[i];
    }
}

void render_gui(SDL_Renderer* renderer) 
{
    for (int i = 0; i < BUTTON_COUNT; i++) 
    {
        SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
        SDL_RenderFillRect(renderer, &buttons[i].rect);

        if (font) {
            SDL_Color textColor = { 255, 255, 255, 255 };
            SDL_Surface* surface = TTF_RenderText_Blended(font, buttons[i].label, textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_Rect textRect = {
                buttons[i].rect.x + 10,
                buttons[i].rect.y + 10,
                surface->w,
                surface->h
            };

            SDL_RenderCopy(renderer, texture, NULL, &textRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
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
    if (font) 
    {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}
