#pragma once
#include <conio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <iomanip>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::vector;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ROWS 4
#define COLS 4

class Tile;
int  score    = 0;
bool bEndGame = false;
bool bBoardChanged = false;

enum Action { Up, Down, Left, Right, ND };
Action currAction = ND;

class Tile
{
  public:
	int iRow;
	int iCol;
	int iVal;
	int iID;
	bool bIsAvailable;

	Tile(int iRow = 9999, int iCol = 9999, int iVal = 9999, int iID = 9999, bool bIsAvailable = true);
};

Tile board[ROWS][COLS];
