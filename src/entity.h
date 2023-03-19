#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include <stdint.h>
#include <stddef.h>

typedef enum {
	EMTPY
} EntityType;

typedef struct entity {
	uint32_t id;

	EntityType type;

	Rectangle body;
	Vector2 velocity;
	Vector2 acceleration;
	Color color;

	struct entity *next;
} Entity;

typedef struct {
	Entity *head;

	uint32_t id_counter;

	Entity **marked_for_removal;
	size_t marked_size;
	uint32_t marked_iterator;
} List;

Entity entity_create(EntityType type, float x, float y, float width, float height);

List   *entity_list_create(void);

Entity *entity_list_get(List *list, uint32_t id);
Entity *entity_list_add(List *list, Entity entity);
void    entity_list_remove(List *list, uint32_t id);

void entity_list_mark_for_removal(List *list, Entity *entity);
void entity_list_remove_marked(List *list);

void entity_list_free(List *list);

void entity_list_print(List *list);

#endif // ENTITY_H
