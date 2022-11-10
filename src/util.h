#pragma once
#include <stdint.h>

typedef struct llist {
	llist* next;
	uint16_t value;
} llist;

void DestroyLList(llist* l);

