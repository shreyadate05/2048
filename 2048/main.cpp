#include <iostream>
#include <random>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>
#include <cstdlib>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int  board[4][4] = { 0 };
int  score       = 0;
bool bEndGame    = false;

enum Action{ Up, Down, Left, Right, ND };
Action currAction = ND;

bool printBoard()
{
	system("cls");
	cout << "SCORE: " << score << endl << endl;

	for (int y = 0; y < 4; y++)
	{
		cout << "+------+------+------+------+" << endl << "| ";
		for (int x = 0; x < 4; x++)
		{
			if (!board[x][y]) 
				cout << setw(4) << " ";
			else 
				cout << setw(4) << board[x][y];
			cout << " | ";
		}
		cout << endl;
	}
	cout << "+------+------+------+------+" << endl << endl;

	return true;
}

bool initializeBoard()
{
	srand(time(NULL));
	int iRow1 = 0 + rand() % (4);
	int iCol1 = 0 + rand() % (4);
	board[iRow1][iCol1] = (rand() > RAND_MAX / 2) ? 2 : 4;

	int iRow2 = 0 + rand() % (4);
	int iCol2 = 0 + rand() % (4);
	board[iRow2][iCol2] = (rand() > RAND_MAX / 2) ? 2 : 4;

	return true;
}

bool getInput()
{
	bool result = true;

	int key = 0;
	_getch();
	switch (result && (key = _getch()))
	{
	case KEY_UP:
		currAction = Action::Up;
		break;

	case KEY_DOWN:
		currAction = Action::Down;
		break;

	case KEY_LEFT:
		currAction = Action::Left;
		break;

	case KEY_RIGHT:
		currAction = Action::Down;
		break;

	default:
		cout << endl << "Invalid Input" << endl;
		currAction = Action::ND;
		result = false;
		break;
	}

	return result;
}

bool moveUp()
{
	bool result;

	return result;
}

bool moveDown()
{
	bool result;

	return result;
}

bool moveLeft()
{
	bool result;

	return result;
}

bool moveRight()
{
	bool result;

	return result;
}

bool move()
{
	bool result = true;

	switch (currAction)
	{
	case Up:
		currAction = Action::Up;
		result = moveUp();
		break;

	case Down:
		currAction = Action::Down;
		result = moveDown();
		break;

	case Left:
		currAction = Action::Left;
		result = moveLeft();
		break;

	case Right:
		currAction = Action::Down;
		result = moveRight();
		break;

	default:
		cout << endl << "Action not defined" << endl;
		result = false;
		break;
	}

	return result;
}

bool gameRun()
{
	if (!getInput())
	{
		bEndGame = true;
		return bEndGame;
	}

	move();

	return true;
}

int main()
{
	initializeBoard();
	printBoard();
	while (!bEndGame)
	{
		gameRun();
	}
	return 0;
}



