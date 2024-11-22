#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
#include <SDL2/SDL.h>

#define TITLE     "random walk"
#define WINDOW_X  0
#define WINDOW_Y  0
#define WINDOW_W  800
#define WINDOW_H  480

void
handle_error (const char *msg);

int
state_render (SDL_Renderer *renderer, gsl_matrix *current_state, SDL_Rect *rect);

int
main (void)
{
  unsigned int steps = 0;

  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;
  unsigned int cell_width, cell_height;
  cell_width  = 4;
  cell_height = 4;
  gsl_matrix *current_state = gsl_matrix_calloc (WINDOW_W / cell_width,
                                        WINDOW_H / cell_height);

  const gsl_rng_type *T;
  gsl_rng *r;
  gsl_rng_env_setup ();
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  if (r == NULL)
    handle_error ("gsl_rng_alloc");

  SDL_Rect cell = {0, 0, cell_width, cell_height};
  
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
    {
      SDL_Quit ();
      handle_error ("SDL_Init");
    }

  window = SDL_CreateWindow (TITLE,
                             WINDOW_X, WINDOW_Y,
                             WINDOW_W, WINDOW_H,
                             0);
                             //SDL_WINDOW_BORDERLESS);
                             //SDL_WINDOW_OPENGL);
  if (window == NULL)
    {
      SDL_DestroyWindow (window);
      handle_error ("SDL_CreateWindow");
    }

  renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL)
    {
      SDL_DestroyRenderer (renderer);
      handle_error ("SDL_CreateRenderer");
    }

  if (SDL_SetRenderDrawColor (renderer, 0xff, 0xff, 0xff, 0xff) != 0)
    handle_error ("SDL_SetRenderDrawColor");

  if (SDL_RenderClear (renderer) != 0)
    handle_error ("SDL_RenderClear");

  SDL_RenderPresent (renderer);

  unsigned int i, j, dir;
  i = gsl_rng_uniform_int (r, WINDOW_W / cell_width);
  j = gsl_rng_uniform_int (r, WINDOW_H / cell_height);
  SDL_Event event;
  unsigned int running = 1;
  while (running)
    {
      while (SDL_PollEvent (&event))
        {
          switch (event.type)
            {
            case SDL_QUIT:
              running = 0;
              break;
            case SDL_KEYDOWN:
              if (event.key.keysym.sym == SDLK_ESCAPE)
                running = 0;
              break;
            }
        }
      /*  loop begin  */
      SDL_RenderClear (renderer);
      if (state_render (renderer, current_state, &cell) != 0)
        handle_error ("state_render");

      dir = gsl_rng_uniform_int (r, 4);
      switch (dir)
        {
        case 0:
          i = i + 1;
          break;
        case 1:
          j = j + 1;
          break;
        case 2:
          i = i - 1;
          break;
        case 3:
          j = j - 1;
          break;
        }

      if (i >= 0 && i < (WINDOW_W / cell_width) && j >= 0 && j < (WINDOW_H / cell_height))
        gsl_matrix_set (current_state, i, j, 1);
      else
        {
        }

      SDL_RenderPresent (renderer);
      SDL_Delay (1);
      ++steps;
      /*  loop end  */
    }

  printf ("%d steps\n", steps);

  gsl_rng_free (r);
  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);
	SDL_Quit ();
	exit (EXIT_SUCCESS);
}

void
handle_error (const char *msg)
{
  perror (msg);
  exit (EXIT_FAILURE);
}

int
state_render (SDL_Renderer *renderer, gsl_matrix *current_state, SDL_Rect *rect)
{
  unsigned int i, j;
  for (i = 0; i < current_state -> size1; i++)
    for (j = 0; j < current_state -> size2; j++)
      {
        rect -> x = i * rect -> w;
        rect -> y = j * rect -> h;
        if ((int)gsl_matrix_get (current_state, i, j) == 0)
          {
            if (SDL_SetRenderDrawColor (renderer, 0xff, 0xff, 0xff, 0xff) != 0)
              return -1;
            if (SDL_RenderDrawRect (renderer, rect) != 0)
              return -1;
          }
        else if ((int)gsl_matrix_get (current_state, i, j) == 1)
          {
            if (SDL_SetRenderDrawColor (renderer, 0x00, 0x00, 0x00, 0xff) != 0)
              return -1;
            if (SDL_RenderFillRect (renderer, rect) != 0)
              return -1;
          }
        else
          {
            return -2;
          }
      }
  return 0;
}

