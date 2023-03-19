#include <stdio.h>
#include <stdlib.h>

#include "entity.h"

Entity entity_create(EntityType type, float x, float y, float width, float height)
{
	Entity entity = {0};

	entity.type = type;
	entity.body.x = x;
	entity.body.y = y;
	entity.body.width = width;
	entity.body.height = height;
	entity.color = WHITE;

	return entity;
}

List *entity_list_create(void)
{
	List *list = malloc(sizeof(List));

	list->id_counter = 1;
	list->head = NULL;
	list->marked_for_removal = malloc(sizeof(Entity **));
	list->marked_size = 1;
	list->marked_iterator = 0;

	return list;
}

Entity *entity_list_get(List *list, uint32_t id)
{
	Entity *temp;
	for (temp = list->head; temp->id != id; temp = temp->next);

	return temp;
}

Entity *entity_list_add(List *list, Entity entity)
{
	if (list->head == NULL) {
		Entity *head = list->head;

		head = malloc(sizeof(Entity));
		*head = entity;
		head->id = list->id_counter++;
		head->next = NULL;

		list->head = head;
		
		return head;
	}

	Entity *temp;
	for (temp = list->head; temp->next != NULL; temp = temp->next);

	temp->next = malloc(sizeof(Entity));
	temp = temp->next;
	*temp = entity;
	temp->id = list->id_counter++;
	temp->next = NULL;

	return temp;
}

void entity_list_remove(List *list, uint32_t id)
{
	if (id >= list->id_counter || list->head == NULL)
		return;

	if (list->head->id == id) {
		Entity *temp = list->head->next;
		free(list->head);
		list->head = temp;

		return;
	}

	Entity *current;
	for (current = list->head; current->next->id != id; current = current->next) {
		if (current->next->next == NULL)
			return;
	}

	Entity *temp = current->next;
	current->next = current->next->next;
	free(temp);
}

void entity_list_mark_for_removal(List *list, Entity *entity)
{
	Entity **marked = list->marked_for_removal;

	if (list->marked_iterator + 1 == list->marked_size)
		marked = realloc(marked, (list->marked_size *= 2) * sizeof(Entity **));

	marked[list->marked_iterator++] = entity;

	list->marked_for_removal = marked;
}

void entity_list_remove_marked(List *list)
{
	if (list->marked_iterator == 0)
		return;

	for (uint32_t i = 0; i < list->marked_iterator; ++i)
		entity_list_remove(list, list->marked_for_removal[i]->id);
	list->marked_iterator = 0;
}

void entity_list_free(List *list)
{
	Entity *head = list->head;
	Entity *prev = NULL;

	while (head != NULL) {
		prev = head;
		head = head->next;
		free(prev);
	}

	list->head = head;
	
	free(list->marked_for_removal);
	free(list);
}

void entity_list_print(List *list)
{
	Entity *temp;
	for (temp = list->head; temp != NULL; temp = temp->next)
		printf("%d | ", temp->id);

	printf("\n");
}
