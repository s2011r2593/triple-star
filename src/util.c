#include <stdlib.h>

#include "util.h"

void DestroyLList(llist* l) {
	llist* current = l;
	do {
		llist* next = current->next;
		free(current);
		current = next;
	} while (current != NULL);
}

