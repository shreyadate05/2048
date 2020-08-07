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
		currAction = Action::Right;
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
	vector<int> temp;

	for (int i = 0; i < vTiles.size(); i++)
	{
		if (vTiles[i] != 0)
		{
			temp.push_back(vTiles[i]);
		}
	}

	if (temp.size() > 1 && temp[0] == temp[1])
	{
		temp[1] = temp[0] * 2;
		temp.erase(temp.begin());
	}

	int diff = vTiles.size() - temp.size();
	for (int i = 0; i < diff; i++)
	{
		vTiles[i] = 0;
	}

	int j = 0;
	for (int i = diff; i < vTiles.size(); i++)
	{
		vTiles[i] = temp[j++];
	}

	return true;
}

bool moveUp()
{
	bool result = true;
	vector<int> vTiles;

	for (int i = 0; i < COLS; i++)
	{
		vTiles.clear();
		for (int j = ROWS - 1; j >= 0; j--)
		{
			vTiles.push_back(board[i][j].iVal);
		}

		updateVector(vTiles);

		int k = 0;
		for (int j = ROWS - 1; j >= 0; j--)
		{
			board[i][j].iVal = vTiles[k];
			k++;
		}
	}

	return result;
}

bool moveDown()
{
	bool result = true;
	vector<int> vTiles;

	for (int i = 0; i < COLS; i++)
	{
		vTiles.clear();
		for (int j = 0; j < ROWS; j++)
		{
			vTiles.push_back(board[i][j].iVal);
		}

		updateVector(vTiles);

		int k = 0;
		for (int j = 0; j < ROWS; j++)
		{
			board[i][j].iVal = vTiles[k];
			k++;
		}
	}

	return result;
}

bool moveLeft()
{
	bool result = true;
	vector<int> vTiles;

	for (int i = 0; i < ROWS; i++)
	{
		vTiles.clear();
		for (int j = COLS - 1; j >= 0; j--)
		{
			vTiles.push_back(board[j][i].iVal);
		}

		updateVector(vTiles);

		int k = 0;
		for (int j = COLS - 1; j >= 0; j--)
		{
			board[j][i].iVal = vTiles[k];
			k++;
		}
	}

	return result;
}

bool moveRight()
{
	bool result = true;
	vector<int> vTiles;

	for (int i = 0; i < ROWS; i++)
	{
		vTiles.clear();
		for (int j = 0; j < COLS; j++)
		{
			vTiles.push_back(board[j][i].iVal);
		}

		updateVector(vTiles);

		int k = 0;
		for (int j = 0; j < COLS; j++)
		{
			board[j][i].iVal = vTiles[k];
			k++;
		}
	}

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
		currAction = Action::Right;
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
	printBoard();

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



