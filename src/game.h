#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include <stdint.h>

#include "list.h"
#include "window.h"
#include "entity.h"

typedef struct {
	Window *window;
	float delta_time;

	List *entities, *textures, *sounds;
} Game;

void game_run(int32_t width , int32_t height, const char *title);

#endif // GAME_H
