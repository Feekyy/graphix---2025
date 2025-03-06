#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdbool.h>
#include <stdio.h>

#define MAX_LINES 10

typedef struct Point
{
  float x;
  float y;
} Point;

typedef struct RGB
{
  const float red;
  const float green;
  const float blue;
} RGB;

typedef struct Line
{
  Point start;
  Point end;
} Line;

Point start_point = {-1, -1};
Point end_point = {-1, -1}; 
bool drawing = false;
RGB line_color = {255, 255, 0};
Line lines[MAX_LINES];
int line_count = 0;

void set_color(RGB color)
{
    glColor3f(color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f);
}

void draw_line(Point start, Point end)
{
  glBegin(GL_LINES);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
  glEnd();
}

int main(int argc, char* argv[])
{


  int error_code;
  SDL_Window* window;
  bool need_run;
  SDL_Event event;
  SDL_GLContext gl_context;
  int i;

  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0) 
  {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow
  (
    "Main Window",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600,
    SDL_WINDOW_OPENGL
  );

  gl_context = SDL_GL_CreateContext(window);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  need_run = true;
  while (need_run) 
  {
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
                      if (!drawing)
                      {
                          start_point.x = event.button.x / (float)800 * 2 - 1;
                          start_point.y = 1 - event.button.y / (float)600 * 2;
                          drawing = true;
                      }
                      else
                      {
                          end_point.x = event.button.x / (float)800 * 2 - 1;
                          end_point.y = 1 - event.button.y / (float)600 * 2;
                          drawing = false;

                          if (line_count < MAX_LINES)
                          {
                              lines[line_count].start = start_point;
                              lines[line_count].end = end_point;
                              line_count++;
                          }
                        
                          start_point = (Point){-1, -1};
                          end_point = (Point){-1, -1};
                      }
                   }
          }
          SDL_GL_SwapWindow(window);
        break;
              
      }


  glClear(GL_COLOR_BUFFER_BIT);

    set_color(line_color);
    for (int i = 0; i < line_count; i++)
    {
        draw_line(lines[i].start, lines[i].end);
    }
  
    if (drawing && start_point.x != -1 && start_point.y != -1)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        Point current_point = {x / (float)800 * 2 - 1, 1 - y / (float)600 * 2};
        draw_line(start_point, current_point);
    }
  }

  SDL_GL_SwapWindow(window);

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
