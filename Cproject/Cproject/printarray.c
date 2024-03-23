#include <stdio.h> // finished
#define MAP_SIZE 6

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

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]) {
	for (int ii = 0; ii < ii + 2; ii++) {
		map[ii][0] = 2;
	}
}


void main(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map1);
	printf("\nMap: \n");
	PrintArray(map1);
}
