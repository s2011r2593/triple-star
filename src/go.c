#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "go.h"

GoState* InitGoState() {
	GoState* g = (GoState*) malloc(sizeof(GoState));
	if (g == NULL) {
		printf("alloc failed\n");
		exit(-1);
	}

	// 2 time steps -> 4 boards
	g->position = (uint8_t**) malloc(4 * sizeof(uint8_t*));
	if (g->position == NULL) {
		printf("alloc failed\n");
		exit(-1);
	}
	
	for (int i = 0; i < 4; i++) {
		g->position[i] = (uint8_t*) calloc(361 * sizeof(uint8_t));
		if (g->position[i] == NULL) {
			printf("alloc failed\n");
			exit(-1);
		}
	}

	g->color = 0;

	return g;
}

void DestroyGoState(GoState* g) {
	for (int i = 0; i < 4; i++) {
		free(g->position[i]);
	}
	free(g->position);
	free(g);
}

void GetContext(uint8_t* board, uint8_t* visited, llist* border, llist* clique, int index) {
	visited[index] = 1;
	llist* me = (llist*) malloc(sizeof(llist));
	if (me == NULL) {
		printf("alloc failed\n");
		exit(-1);
	}
	me->value = index;
	me->next = NULL;

	if (board[index]) {
		llist* c = clique;
		while (c->next != NULL) {
			c = c->next;
		}
		c->next = me;
		
		int neighbor = index - 19;
		if (index > 18 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
		neighbor = index + 1;
		if (index % 19 != 18 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
		neighbor = index + 19;
		if (index < 342 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
		neighbor = index - 1;
		if (index % 19 != 0 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
	} else {
		llist* b = border;
		while (b->next != NULL) {
			b = b->next;
		}
		b->next = me;
	}
}

llist* IsCaptured(GoState* g, int index) {
	uint8_t* visited = (uint8_t*) calloc(361 * sizeof(uint8_t));
	if (visited == NULL) {
		printf("alloc failed\n");
		exit(-1);
	}
	llist* border = (llist*) malloc(sizeof(llist));
	if (border == NULL) {
		printf("alloc failed\n");
		exit(-1);
	}
	llist* clique = (llist*) malloc(sizeof(llist));
	if (clique == NULL) {
		printf("alloc failed\n");
		exit(-1);
	}
	border->next = NULL;
	clique->next = NULL;

	GetContext(g->position[g->color], visited, border, clique, index);
	
	uint8_t opponent = g->color;
	llist* b = border;
	while (b->next != NULL) {
		b = b->next;
		liberties += 1 - g->position[opponent][b->value]
	}

	DestroyLList(clique);
	DestroyLList(border);
	free(visited);
}

