#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "graphics/window.h"
#include "entities/entity.h"

typedef struct {
	Window *window;
	float delta_time;

	List *entities, *textures, *sounds, *music;
} Game;

void game_run(void);

#endif // GAME_H
