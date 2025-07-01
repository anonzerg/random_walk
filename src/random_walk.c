#include "random_walk.h"

void
handle_error (const char *msg)
{
  perror (msg);
  exit (EXIT_FAILURE);
}

int
state_render (SDL_Renderer *renderer, gsl_matrix *current_state,
              SDL_Rect *rect)
{
  unsigned int i, j;
  for (i = 0; i < current_state->size1; i++)
    for (j = 0; j < current_state->size2; j++)
      {
        rect->x = i * rect->w;
        rect->y = j * rect->h;
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
