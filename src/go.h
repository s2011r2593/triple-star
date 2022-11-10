#pragma once
#include <stdint.h>

typedef struct GoState {
	uint8_t** position;
	uint8_t color;
} GoState;

GoState* InitGoState();
void DestroyGoState(GoState* g);

