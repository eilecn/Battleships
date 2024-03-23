#include <stdio.h>
#define MAP_SIZE 6

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]) {
	int r;
	int rowposition, colposition, orientation;
	r = rand();
	rowposition = r % MAP_SIZE;
	r = rand();
	colposition = r % MAP_SIZE;
	r = rand();
	orientation = r % 2; // 1 vertical 0 horizontal

	if (orientation == 1) {
		if (rowposition + size > MAP_SIZE - 1) {
			rowposition = rowposition - (rowposition + size - MAP_SIZE);
		}
	}

	if (orientation == 0) {
		if (colposition + size > MAP_SIZE - 1) {
			colposition = colposition - (colposition + size - MAP_SIZE);
		}
	}

	int i;
	int j;
	if (orientation == 1) {
		for (i = 0; i < size; i++) {
			map[rowposition + i][colposition] == size;
		}
	}

	if (orientation == 0) {
		for (j = 0; j < size; j++) {
			map[rowposition][colposition + j] == size;
		}
	}

}