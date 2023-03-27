#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "entity.h"
#include "game.h"

static Game *init(int32_t width, int32_t height, const char *title);

static void update(Game *game);
static void render(Game *game);

static void terminate(Game *game);

static Game *init(int32_t width, int32_t height, const char *title)
{
	Game *game = malloc(sizeof(Game));

	game->window = window_init(width, height, title);
	InitAudioDevice();

	game->entities = list_create();

	return game;
}

void game_run(int32_t width , int32_t height, const char *title)
{
	Game *game = init(width, height, title);

	Entity *entity = list_add(game->entities, entity_create(0, 0, 0, 100.0f, 100.0f), sizeof(Entity))->data;
	entity->color = BLUE;

	while (!window_should_close()) {
		game->delta_time = GetFrameTime();

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
	
	for (Node *temp = game->entities->head; temp != NULL; temp = temp->next) {
		DrawRectangleRec(((Entity *)temp->data)->body, ((Entity *)temp->data)->color);
	}

	EndDrawing();
}

static void terminate(Game *game)
{
	window_destroy(game->window);
	list_free(game->entities);
	free(game);
}
