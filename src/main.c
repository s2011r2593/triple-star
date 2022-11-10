#include <stdint.h>
#include <stdio.h>
#include <locale.h>

#include "go.h"

int main() {
	setlocale(LC_CTYPE, "");
	
	GoState* game = InitGoState();

	game->position[0][0] = 1;
	game->position[0][1] = 1;
	game->position[1][19] = 1;
	game->position[1][20] = 1;
	game->position[1][2] = 1;

	PrintGoPosition(game);

	uint8_t captured = IsCaptured(game, 0);
	printf("%d\n", captured);

	DestroyGoState(game);

	return 0;
}

