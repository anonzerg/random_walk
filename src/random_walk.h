#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
#include <SDL2/SDL.h>

#define TITLE "random walk"
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_W 800
#define WINDOW_H 480

void
handle_error (const char *msg);

int
state_render (SDL_Renderer *renderer, gsl_matrix *current_state, SDL_Rect *rect);

#endif /* RANDOM_WALK_H  */

