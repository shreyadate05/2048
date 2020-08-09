#include "2048.h"

Tile::Tile(int iRow, int iCol, int iVal, int iID, bool bIsAvailable)
{
	iRow = iRow;
	iCol = iCol;
	iVal = iVal;
	iID  = iID;
	bIsAvailable = bIsAvailable;
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

int getRandomWithExclusion()
{
	vector<int> excludes;
	for (int i = 0; i < vAvailable.size(); i++)
	{
		if (!vAvailable[i])
		{
			excludes.push_back(i);
		}
	}

	unsigned int max = (COLS * ROWS) - excludes.size();
	int random = (rand() % max);
	for (unsigned int i = 0; i < excludes.size(); i++)
	{
		int ex = excludes[i];
		if (random < ex) 
		{
			break;
		}
		random++;
	}

	return random;
}

bool generateRandomNumberOnBoard()
{
	srand(time(NULL));
	int randomIndex = getRandomWithExclusion();

	vAvailable[randomIndex] = false;
	int i = randomIndex / COLS;
	int j = randomIndex % COLS;
	
	board[i][j].iVal = (rand() > RAND_MAX / 2) ? 2 : 4;
	board[i][j].bIsAvailable = false;
	
	return true;
}

bool initializeBoard()
{
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			board[i][j].iRow = i;
			board[i][j].iCol = j;
			board[i][j].iVal = 0;
			board[i][j].bIsAvailable = true;
			board[i][j].iID = i*ROWS + j;
			vAvailable.push_back(true);
		}
	}

	generateRandomNumberOnBoard();
	generateRandomNumberOnBoard();

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

bool updateAvailability()
{
	bool result = true;

	for (int x = 0; x < COLS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			if (board[x][y].iVal == 0)
			{
				board[x][y].bIsAvailable    = true;
				vAvailable[board[x][y].iID] = true;
			}
			else
			{
				board[x][y].bIsAvailable    = false;
				vAvailable[board[x][y].iID] = false;
			}
		}
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

	int i = temp.size() - 1;
	while (i >= 0)
	{
		bool bIsValidIndex = temp.size() > 1 && i > 0;
		if (bIsValidIndex && temp[i] == temp[i - 1])
		{
			temp[i] = temp[i-1] * 2;
			temp.erase(temp.begin() + i - 1);
		}
		i--;
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
	updateAvailability();
	generateRandomNumberOnBoard();
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
