/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
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

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int* row, int* col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char* boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i % 10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i % 10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len + 1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				}
				else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			}
			else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			}
			else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				}
				else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			}
			else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			}
			else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len + 1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE - 2; i++) {
			strcat(boardString, "*");
		}
	}
	else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE - 2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2 * MAP_SIZE + 5) * (MAP_SIZE + 5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = { 0 };
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = { 0 };

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = { 0 };
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = { 0 };

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			}
			else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}
		else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			}
			else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row + 'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}
		else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			}
			else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		}
		else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	}
	else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













