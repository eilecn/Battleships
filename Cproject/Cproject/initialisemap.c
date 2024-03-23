#include <stdio.h>
#define MAP_SIZE 6

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]) {
	int i;
	int j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (i >= 1 && i <= 5 && j == MAP_SIZE-1) {
				map[i][j] = 5;
			}
			else if (i == 1 && j <= 3) {
				map[i][j] = 4;
			}
			else if (i >= MAP_SIZE/2 && i<= MAP_SIZE/2+2 && j == MAP_SIZE/2) {
				map[i][j] = 3;
			}
			else if (i == MAP_SIZE/2+1 && j <= 1) {
				map[i][j] = 2;
			}

		}
		printf("\n");
	}
}

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	int i;
	int j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			printf("%d", values[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}


void main(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map1);
	printf("Map: \n");
	PrintArray(map1);
}
