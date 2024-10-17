#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define CELL_SIDE 20

void
render_grid (SDL_Renderer *renderer);

int
main (void)
{
	bool running = true;

	if (SDL_Init (SDL_INIT_VIDEO) != 0)
		{
			fprintf (stderr, "[-] SDL_Init failed: %s\n",
							 SDL_GetError ());
			exit (EXIT_FAILURE);
		}

	SDL_Window *window = NULL;
	window = SDL_CreateWindow ("random walk",
														 SDL_WINDOWPOS_CENTERED,
														 SDL_WINDOWPOS_CENTERED,
														 WINDOW_WIDTH,
														 WINDOW_HEIGHT,
														 SDL_WINDOW_BORDERLESS);
	if (!window)
		{
			fprintf (stderr, "[-] SDL_CreateWindow failed: %s\n",
							 SDL_GetError ());
			exit (EXIT_FAILURE);
		}

	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		{
			fprintf (stderr, "[-] SDL_CreateRenderer failed: %s\n",
							 SDL_GetError ());
			exit (EXIT_FAILURE);
		}

	SDL_SetRenderDrawColor (renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear (renderer);
	SDL_RenderPresent (renderer);

	SDL_Event event;
	while (running)
		{
			while (SDL_PollEvent (&event))
				{
					switch (event.type)
						{
							case SDL_QUIT:
								running = false;
								break;
							case SDL_KEYDOWN:
								if (event.key.keysym.sym == SDLK_ESCAPE)
									running = false;
								break;
						}
				}

			SDL_RenderClear (renderer);
			// running loop begins
			render_grid (renderer);
			// running loop ends
		}

	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
	SDL_Quit ();
	exit (EXIT_SUCCESS);
}

void
render_grid (SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor (renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_Rect rect;
	rect.w = CELL_SIDE;
	rect.h = CELL_SIDE;

	int i, j;
	for (i = 0; i < WINDOW_WIDTH / CELL_SIDE; i++)
		for (j = 0; j < WINDOW_HEIGHT / CELL_SIDE; j++)
			{
				rect.x = i * CELL_SIDE;
				rect.y = j * CELL_SIDE;
				printf ("(%d, %d)\n", rect.x, rect.y);
				SDL_RenderFillRect (renderer, &rect);
			}
	return;
}

