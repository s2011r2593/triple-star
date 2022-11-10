#pragma once
#include <stdint.h>

typedef struct llist {
	struct llist* next;
	uint16_t value;
} llist;

void DestroyLList(llist* l);

