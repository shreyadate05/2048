#include "2048.h"

Tile::Tile(int iRow, int iCol, int iVal, bool bIsAvailable)
{
	iRow = iRow;
	iCol = iCol;
	iVal = iVal;
	bIsAvailable = false;
}

bool printBoard()
{
	//system("cls");
	cout << "SCORE: " << score << endl << endl;

	for (int y = 0; y < COLS; y++)
	{
		cout << "+------+------+------+------+" << endl << "| ";
		for (int x = 0; x < ROWS; x++)
		{
			if (!board[x][y].iVal) 
				cout << setw(4) << " ";
			else 
			cout << setw(4) << board[x][y].iVal;
			cout << " | ";
		}
		cout << endl;
	}
	cout << "+------+------+------+------+" << endl << endl;

	return true;
}

bool initializeBoard()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j].iRow = i;
			board[i][j].iCol = j;
			board[i][j].iVal = 0;
			board[i][j].bIsAvailable = true;
		}
	}

	srand(time(NULL));
	int iRow1 = 0 + rand() % (4);
	int iCol1 = 0 + rand() % (4);
	board[iRow1][iCol1].iVal = (rand() > RAND_MAX / 2) ? 2 : 4;

	int iRow2 = 0 + rand() % (4);
	int iCol2 = 0 + rand() % (4);
	board[iRow2][iCol2].iVal = (rand() > RAND_MAX / 2) ? 2 : 4;

	return true;
}

bool getInput()
{
	bool result = true;

	int key = 0;

	_getch();
	switch (key = _getch())
	{
		cout << "\nkey: " << key;
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

bool updateVector(vector<int>& vTiles)
{
	// find first occurrence of non-zero number
	int i = 0;
	while (i < vTiles.size() && vTiles[i] == 0)
	{
		i++;
	}

	// all elements in vector are 0
	// or all except last element in vector are 0
	if (i == vTiles.size() || i == vTiles.size() - 1)
	{
		return true;
	}

	// record index and val of first occurrence of non-zero number
	int startIndex = i;
	int start = vTiles[startIndex];

	// find second occurrrence of non-zero number
	i = startIndex + 1;
	while (i < vTiles.size() && vTiles[i] == 0)
	{
		i++;
	}

	// all elements in vector are 0
	if (i == vTiles.size())
	{
		vTiles[i-1] = start;
		vTiles[startIndex] = 0;
		return true;
	}

	// record index and val of second occurrence of non-zero number
	int endIndex = i;
	int end = vTiles[endIndex];

	// if num are equal, double them
	if (start == end)
	{
		vTiles[endIndex] = start * 2;
		vTiles[startIndex] = 0;
	}

	return true;
}

bool moveUp()
{
	bool result = true;
	vector<int> vTiles;

	for (int i = 0; i < COLS; i++)
	{
		cout << "\n===================================\n\n";

		vTiles.clear();
		for (int j = ROWS - 1; j >= 0; j--)
		{
			vTiles.push_back(board[i][j].iVal);
		}
		
		for (int j = 0; j < vTiles.size(); j++)
		{
			cout << vTiles[j] << ", ";
		}
		updateVector(vTiles);

		int k = 0;
		for (int j = ROWS - 1; j >= 0; j--)
		{
			board[i][j].iVal = vTiles[k];
			k++;
		}

		printBoard();
	}


	return result;
}

bool moveDown()
{
	bool result = true;

	return result;
}

bool moveLeft()
{
	bool result = true;

	return result;
}

bool moveRight()
{
	bool result = true;

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



