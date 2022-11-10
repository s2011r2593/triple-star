#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "go.h"

// Returns a pointer to a default Go game
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
	
	// Initializes boards
	for (int i = 0; i < 4; i++) {
		g->position[i] = (uint8_t*) calloc(361, sizeof(uint8_t));
		if (g->position[i] == NULL) {
			printf("alloc failed\n");
			exit(-1);
		}
	}

	g->color = 0;

	return g;
}

// Frees a Go game
void DestroyGoState(GoState* g) {
	for (int i = 0; i < 4; i++) {
		free(g->position[i]);
	}
	free(g->position);
	free(g);
}

// Finds status of surrounding stones
void GetContext(uint8_t* board, uint8_t* visited, llist* border, llist* clique, int index) {
	// Set visited to prevent infinite recursion
	visited[index] = 1;

	// Will add current space to either clique or border
	llist* me = (llist*) malloc(sizeof(llist));
	if (me == NULL) {
		printf("alloc failed\n");
		exit(-1);
	}
	me->value = index;
	me->next = NULL;

	if (board[index]) {
		// If current space is a friendly stone, add to clique
		llist* c = clique;
		while (c->next != NULL) {
			c = c->next;
		}
		c->next = me;
		
		// Check neighboring spaces
		// North
		int neighbor = index - 19;
		if (index > 18 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
		// East
		neighbor = index + 1;
		if (index % 19 != 18 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
		// South
		neighbor = index + 19;
		if (index < 342 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
		// West
		neighbor = index - 1;
		if (index % 19 != 0 && visited[neighbor] == 0) {
			GetContext(board, visited, border, me, neighbor);
		}
	} else {
		// If current space is not a friendly stone, add to border
		// End this branch of the search.
		llist* b = border;
		while (b->next != NULL) {
			b = b->next;
		}
		b->next = me;
	}
}

// Finds if a stone is captured or not
uint8_t IsCaptured(GoState* g, int index) {
	uint8_t* visited = (uint8_t*) calloc(361, sizeof(uint8_t));
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

	// Finds border and friendly stones
	GetContext(g->position[g->color], visited, border, clique, index);
	
	// Check if there are any holes in the border
	uint8_t captured = 1;
	uint8_t opponent = 1 - g->color;
	llist* b = border;
	while (b->next != NULL) {
		b = b->next;
		if (g->position[opponent][b->value] == 0) {
			captured = 0;
			break;
		}
	}

	DestroyLList(clique);
	DestroyLList(border);
	free(visited);

	return captured;
}

