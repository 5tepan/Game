#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, xFrut, yFrut, score;
enum eDirection {STOP = 0, LEFT, RIGHT, DOWN, UP};
eDirection dir;
int tailX[100], tailY[100];
int tailN;


void Setup() //настройки
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	xFrut = rand() % width;
	yFrut = rand() % height;
	score = 0;
}

void Drow() //карта
{
	system("cls"); // чистим консоль
	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == yFrut && j == xFrut)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < tailN; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if(!print)
				cout << " ";
			}
		}
		cout << endl;
	}


	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input() //клавиши управления
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'z':
			gameOver = true;
			cout << "GAMEOVER	" << "SCORE = " << score << endl;
			break;
		}
	}
}

void Logic() //логика
{
	int lastX = tailX[0];
	int	lastY = tailY[0];
	int last2X, last2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < tailN; i++)
	{
		last2X = tailX[i];
		last2Y = tailY[i];
		tailX[i] = lastX;
		tailY[i] = lastY;
		lastX = last2X;
		lastY = last2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	case UP:
		y--;
		break;
	}

	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}

	for (int i = 0; i < tailN; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == xFrut && y == yFrut)
	{
		score += 10;
		xFrut = rand() % width;
		yFrut = rand() % height;
		tailN++;
	}
}


int main()
{
    Setup();
	while (!gameOver)
	{
		Drow();
		Input();
		Logic();
	}
    return 0;
}

