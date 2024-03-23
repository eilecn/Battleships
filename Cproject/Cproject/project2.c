/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 7
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int* row, int* col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

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

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	int i;
	int j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (i >= 1 && i <= 5 && j == MAP_SIZE - 1) {
				map[i][j] = 5;
			}
			else if (i == 1 && j <= 3) {
				map[i][j] = 4;
			}
			else if (i >= MAP_SIZE / 2 && i <= MAP_SIZE / 2 + 2 && j == MAP_SIZE / 2) {
				map[i][j] = 3;
			}
			else if (i == MAP_SIZE / 2 + 1 && j <= 1) {
				map[i][j] = 2;
			}
			else {
				map[i][j] = 0;
			}
		}
	}
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
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
			map[rowposition + i][colposition] = size;
		}
	}

	if (orientation == 0) {
		for (j = 0; j < size; j++) {
			map[rowposition][colposition + j] = size;
		}
	}
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	int count = 0;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == value) {
				count++;
			}
		}
	}
	return count;
}

int TopLeftPosition(int size, int* row, int* col, int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == size) {
				*row = i;
				*col = j;
				if (map[i][j + 1] == size) {
					return 1; // horizontal
				}
				else {
					return 2; // vertical
				}
			}
		}
	}
	return 0;
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int i, orientation, row, col;

	orientation = TopLeftPosition(size, &row, &col, map);

	if (CountValues(size, map) != size) {
		return 0;
	}
	

	if (orientation == 1) { //horizontal
		if (col != 0) { // checking left
			if (map[row][col - 1] != 0) {
				return 0;
			}
		}

		if (col + size < MAP_SIZE) { // checking right
			if (map[row][col + size] != 0) {
				return 0;
			}
		}

		for (i = 0; i < size; i++) {
			if (row == 0) { // top of board
				if (map[row + 1][col + i] != 0 || map[row][col + i] != size) {
					return 0;
				}
			}
			else if (row + 1 > MAP_SIZE - 1) { // bottom of board
				if (map[row - 1][col + i] != 0 || map[row][col + i] != size) {
					return 0;
				}
			}
			else {  // middle of board
				if (map[row - 1][col + i] != 0 || map[row + 1][col + i] != 0 || map[row][col + i] != size) { // middle of board
					return 0;
				}


			}
		}
		return 1;
	}

	if (orientation == 2) { // vertical
		if (row != 0) { // checking top
			if (map[row - 1][col] != 0) {
				return 0;
			}
		}

		if (row + size < MAP_SIZE) { //checking bottom
			if (map[row + size][col] != 0) {
				return 0;
			}
		}

		for (i = 0; i < size; i++) {
			if (col == 0) { // vertical against left side
				if (map[row + i][col + 1] != 0 || map[row + i][col] != size) {
					return 0;
				}
			}
			else if (col + 1 > MAP_SIZE - 1) { // vertical against right side 
				if (map[row + i][col - 1] != 0 || map[row + i][col] != size) {
					return 0;
				}
			}
			else {
				if (map[row + i][col - 1] != 0 || map[row + i][col + 1] != 0 || map[row + i][col] != size) {
					return 0;
				}

			}
		}
	}
	return 1;
}


void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{
	int j, k;

	AddRandomShip(5, map);
	AddRandomShip(4, map);
	AddRandomShip(3, map);
	AddRandomShip(2, map);

	while (IsShipValid(5, map) + IsShipValid(4, map) + IsShipValid(3, map) + IsShipValid(2, map) != 4) {
		for (k = 0; k < MAP_SIZE; k++) {
			for (j = 0; j < MAP_SIZE; j++) {
				map[k][j] = 0;
			}
		}
		AddRandomShip(5, map);
		AddRandomShip(4, map);
		AddRandomShip(3, map);
		AddRandomShip(2, map);
	}
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	int shotnumber = 1;
	int i, j;

	if (shots[row][col] != 0) {
		return;
	}

	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots[i][j] != 0) {
				shotnumber++;
			}
		}
	}

	if (shots[row][col] == 0) {
		shots[row][col] = shotnumber;
	}

	if (map[row][col] != 0 && shots[row][col] < 1000) {
		shots[row][col] = shots[row][col] + 1000;
	}

	// FIVE BOAT

	int fiverow1, fiverow2, fiverow3, fiverow4, fiverow5;
	int fivecol1, fivecol2, fivecol3, fivecol4, fivecol5;
	int orientation;

	orientation = TopLeftPosition(5, &fiverow1, &fivecol1, map);

	if (orientation == 1) { // horizontal
		fiverow2 = fiverow1;
		fiverow3 = fiverow1;
		fiverow4 = fiverow1;
		fiverow5 = fiverow1;

		fivecol2 = fivecol1 + 1;
		fivecol3 = fivecol2 + 1;
		fivecol4 = fivecol3 + 1;
		fivecol5 = fivecol4 + 1;
	}
	else { //vertical
		fivecol2 = fivecol1;
		fivecol3 = fivecol1;
		fivecol4 = fivecol1;
		fivecol5 = fivecol1;

		fiverow2 = fiverow1 + 1;
		fiverow3 = fiverow2 + 1;
		fiverow4 = fiverow3 + 1;
		fiverow5 = fiverow4 + 1;
	}

	if (shots[fiverow1][fivecol1] > 1000 && shots[fiverow2][fivecol2] > 1000 && shots[fiverow3][fivecol3] > 1000 && shots[fiverow4][fivecol4] > 1000 && shots[fiverow5][fivecol5] > 1000) {
		if (shots[fiverow1][fivecol1] < 1700 && shots[fiverow2][fivecol2] < 1700 && shots[fiverow3][fivecol3] < 1700 && shots[fiverow4][fivecol4] < 1700 && shots[fiverow5][fivecol5] < 1700) {
			shots[fiverow1][fivecol1] = shots[fiverow1][fivecol1] + 4000;
			shots[fiverow2][fivecol2] = shots[fiverow2][fivecol2] + 4000;
			shots[fiverow3][fivecol3] = shots[fiverow3][fivecol3] + 4000;
			shots[fiverow4][fivecol4] = shots[fiverow4][fivecol4] + 4000;
			shots[fiverow5][fivecol5] = shots[fiverow5][fivecol5] + 4000;
		}

	}

	// FOUR BOAT

	int fourrow1, fourrow2, fourrow3, fourrow4;
	int fourcol1, fourcol2, fourcol3, fourcol4;
	orientation = TopLeftPosition(4, &fourrow1, &fourcol1, map);

	if (orientation == 1) { // horizontal
		fourrow2 = fourrow1;
		fourrow3 = fourrow1;
		fourrow4 = fourrow1;

		fourcol2 = fourcol1 + 1;
		fourcol3 = fourcol2 + 1;
		fourcol4 = fourcol3 + 1;
	}
	else { //vertical
		fourcol2 = fourcol1;
		fourcol3 = fourcol1;
		fourcol4 = fourcol1;

		fourrow2 = fourrow1 + 1;
		fourrow3 = fourrow2 + 1;
		fourrow4 = fourrow3 + 1;
	}

	if (shots[fourrow1][fourcol1] > 1000 && shots[fourrow2][fourcol2] > 1000 && shots[fourrow3][fourcol3] > 1000 && shots[fourrow4][fourcol4] > 1000) {
		if (shots[fourrow1][fourcol1] < 1700 && shots[fourrow2][fourcol2] < 1700 && shots[fourrow3][fourcol3] < 1700 && shots[fourrow4][fourcol4] < 1700) {
			shots[fourrow1][fourcol1] = shots[fourrow1][fourcol1] + 3000;
			shots[fourrow2][fourcol2] = shots[fourrow2][fourcol2] + 3000;
			shots[fourrow3][fourcol3] = shots[fourrow3][fourcol3] + 3000;
			shots[fourrow4][fourcol4] = shots[fourrow4][fourcol4] + 3000;
		}
	}

	// THREE BOATs

	int threerow1, threerow2, threerow3;
	int threecol1, threecol2, threecol3;
	orientation = TopLeftPosition(3, &threerow1, &threecol1, map);

	if (orientation == 1) { // horizontal
		threerow2 = threerow1;
		threerow3 = threerow1;

		threecol2 = threecol1 + 1;
		threecol3 = threecol2 + 1;
	}
	else { //vertical
		threecol2 = threecol1;
		threecol3 = threecol1;

		threerow2 = threerow1 + 1;
		threerow3 = threerow2 + 1;
	}

	if (shots[threerow1][threecol1] > 1000 && shots[threerow2][threecol2] > 1000 && shots[threerow3][threecol3] > 1000) {
		if (shots[threerow1][threecol1] < 1700 && shots[threerow2][threecol2] < 1700 && shots[threerow3][threecol3] < 1700) {
			shots[threerow1][threecol1] = shots[threerow1][threecol1] + 2000;
			shots[threerow2][threecol2] = shots[threerow2][threecol2] + 2000;
			shots[threerow3][threecol3] = shots[threerow3][threecol3] + 2000;
		}
	}

	// TWO BOAT

	int tworow1, tworow2;
	int twocol1, twocol2;
	orientation = TopLeftPosition(2, &tworow1, &twocol1, map);

	if (orientation == 1) { // horizontal
		tworow2 = tworow1;

		twocol2 = twocol1 + 1;
	}
	else { //vertical
		twocol2 = twocol1;

		tworow2 = tworow1 + 1;
	}

	if (shots[tworow1][twocol1] > 1000 && shots[tworow2][twocol2] > 1000) {
		if (shots[tworow1][twocol1] < 1700 && shots[tworow2][twocol2] < 1700) {
			shots[tworow1][twocol1] = shots[tworow1][twocol1] + 1000;
			shots[tworow2][twocol2] = shots[tworow2][twocol2] + 1000;
		}
	}
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	int count1 = 0;
	int count2 = 0;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] > 0) {
				count1++;
			}
			if (shots[i][j] > 2000) {
				count2++;
			}
		}
	}

	if (count1 == count2) {
		return 1;
	}
	else {
		return 0;
	}
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

/*************************************************************************
** You should define your own test functions below
*************************************************************************/

// Example: a test function for Task One
void TestPrintArray(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = { 0 };
	printf("Map 1: \n");
	PrintArray(map1);

	int map2[MAP_SIZE][MAP_SIZE] = { 0 };
	for (int i = 0; i < MAP_SIZE; i++) {
		map2[MAP_SIZE - i - 1][i] = i;
	}
	printf("\nMap 2:\n");
	PrintArray(map2);
}

// Example: a test function for Task Two
void TestInitialiseMap(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map1);
	printf("\nMap: \n");
	PrintArray(map1);
}

// Example: a test function for Task Three
void TestAddRandomShip(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = { 0 };
	int map2[MAP_SIZE][MAP_SIZE] = { 0 };

	AddRandomShip(5, map1);

	printf("\nMap: \n");
	PrintArray(map1);

	AddRandomShip(2, map2);
	AddRandomShip(3, map2);
	AddRandomShip(4, map2);
	AddRandomShip(5, map2);

	printf("\nMap: \n");
	PrintArray(map2);
}

void TestCountValues(void)
{
	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	int count, shipSize;
	InitialiseMap(map);
	PrintArray(map);
	for (shipSize = 2; shipSize <= 5; shipSize++) {
		count = CountValues(shipSize, map);
		printf("The value %d appears %d times\n", shipSize,
			count);
	}
}

void TestTopLeftPosition(void)
{
	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	int row, col, direction, shipSize;
	InitialiseMap(map);
	PrintArray(map);
	for (shipSize = 2; shipSize <= 5; shipSize++) {
		direction = TopLeftPosition(shipSize, &row, &col, map);
		printf("Ship %d is at (%d, %d) facing %d\n", shipSize,
			row, col, direction);
	}
}

void TestIsShipValid(void)
{
	// FOR THIS TEST, MAP_SIZE WILL BE 7

	int valid, shipSize;
	int map[7][7] = {
	  {0, 0, 0, 0, 0, 0, 4},
	  {0, 0, 0, 3, 3, 3, 4},
	  {0, 0, 0, 0, 0, 0, 4},
	  {2, 2, 0, 0, 0, 0, 4},
	  {0, 0, 0, 0, 0, 0, 0},
	  {5, 5, 5, 5, 5, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0}
	};
	for (shipSize = 2; shipSize <= 5; shipSize++) {
		valid = IsShipValid(shipSize, map);
		printf("Is ship %d valid? %d\n", shipSize, valid);
	}
}

void TestInitialiseRandomMap(void)
{
	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseRandomMap(map);
	PrintArray(map);
}

void TestFireShot(void)
{

	int map[MAP_SIZE][MAP_SIZE] = {
	{0, 4, 4, 4, 4, 0},
	{0, 0, 0, 0, 0, 0},
	{5, 5, 5, 5, 5, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 3, 3, 3},
	{0, 2, 2, 0, 0, 0}
	};

	int shots[MAP_SIZE][MAP_SIZE] = { 0 };
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE - 1; j++) {
			FireShot(shots, map, i, j);
		}
	}

	PrintArray(shots);
}

void TestCheckGameOver(void)
{
	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	int shots[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map);
	printf("Map:\n");
	PrintArray(map);
	printf("Shots:\n");
	PrintArray(shots);
	while (!CheckGameOver(shots, map)) {
		FireShot(shots, map, rand() % MAP_SIZE, rand() % MAP_SIZE);
	}
	PrintArray(shots);
}



int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	//TestPrintArray();
	//TestInitialiseMap();
	//TestAddRandomShip();
	//TestCountValues();
	//TestTopLeftPosition();
	TestIsShipValid();
	//TestInitialiseRandomMap();
	//TestFireShot();
	//TestCheckGameOver();

	return 0;
}


