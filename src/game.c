#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "game.h"
#include "window.h"

static Game *init(int32_t width, int32_t height, const char *title);

static void update(Game *game);
static void render(Game *game);

static void terminate(Game *game);

static Game *init(int32_t width, int32_t height, const char *title)
{
	Game *game = malloc(sizeof(Game));

	game->window = window_init(width, height, title);
	game->entities = entity_list_create();

	return game;
}

void game_run(int32_t width , int32_t height, const char *title)
{
	Game *game = init(width, height, title);

	while (!window_should_close()) {
		update(game);
		render(game);
	}

	terminate(game);
}

static void update(Game *game)
{
	window_update(game->window);
}

static void render(Game *game)
{
	BeginDrawing();
	ClearBackground(game->window->background);

	EndDrawing();
}

static void terminate(Game *game)
{
	window_destroy(game->window);
	entity_list_free(game->entities);
	free(game);
}
