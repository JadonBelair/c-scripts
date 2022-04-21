#pragma once

#define BLACK 0x0020
#define WHITE 0x2588
#define ROWS 109
#define COLS 472

int generate(int left, int center, int right, int rule);

void copy(int source[], int dest[], int size);
