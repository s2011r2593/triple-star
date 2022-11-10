#pragma once
#include <stdint.h>

typedef struct GoState {
	uint8_t** position;
	uint8_t color;
} GoState;

GoState* InitGoState();
void DestroyGoState(GoState* g);
void PrintGoPosition(GoState* g);
uint8_t IsCaptured(GoState* g, int index);

