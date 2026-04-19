#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include <ctime> 
#include<string>
#include<cstdlib>
#include<fstream>

using namespace std;

const int height = 30, width = 60;
int tailX[200];
int tailY[200];
int otail;

int snakeX, snakeY, fruitX, fruitY;
int score;
char direc;
bool gameover;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void Cursor_setPosition(int col, int row)	//Flickering Control
{
	cout << "\033[" + to_string(row + 1) + ";" + to_string(col + 1) + "H";
}

int record()			//Write function
{
	ofstream MyFile("Record.txt");
	if (!MyFile) {  
		cout << "Error opening the file for writing!" << endl;
		return 1;
	}

	
	MyFile << score << endl;
	

	
	MyFile.close();
}

void startup()
{
	gameover = false;
	snakeX = width / 2;
	snakeY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	otail = 0;
}

void boundry()
{
	Cursor_setPosition(0, 0);
	
	for (int i = 0; i < width+2; i++)		//Top Border
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";   //Side Boundry
			}
			if (i == snakeY && j == snakeX)  //Snake Head
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)   //Fruit
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < otail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "*";
						print = true;
					}
				}
				if (!print)			//Inner Field
				{
					cout << " ";
				}
			}
			if (j == width - 1)
			{
				cout << "#";   //Side Boundry
			}

		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)		//Bottom Border
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score:" << score << endl;
}

void gameplay()
{
	if (_kbhit())
	{
		switch (_getch())  //Controls
		{
		case KEY_UP:		//Move upward
		case 'w':
		case 'W':
		{
			direc = 'w';
			break;
		}
		case KEY_LEFT:		//Move to Left
		case 'a':
		case 'A':
		{
			direc = 'a';
			break;
		}
		case KEY_RIGHT:		//Move to Right
		case 'd':
		case 'D':
		{
			direc = 'd';
			break;
		}
		case KEY_DOWN:		//Move downward
		case 's':
		case 'S':
		{
			direc = 's';
			break;
		}
		}
	}
}

void logic()
{
	int preX = tailX[0];
	int preY = tailY[0];
	int pre2X;
	int pre2Y;
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	for (int i = 1; i < otail; i++)		//Tail tracking
	{
		pre2X = tailX[i];
		pre2Y = tailY[i];
		tailX[i] = preX;
		tailY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
	}
	switch (direc)
	{
	case 'w':	//Up
		snakeY--;
		break;

	case 's':	//Down
		snakeY++;
		break;

	case 'a':	//Left
		snakeX--;
		break;

	case 'd':	//Right
		snakeX++;
		break;
	default:
		break;
	}

	if (snakeX > width || snakeX < 0 || snakeY > height || snakeY < 0)		//Boundry collision check
	{
		gameover = true;
	}
	for (int i = 0; i < otail; i++)			//Tail collision check
	{
		if (tailX[i] == snakeX && tailY[i] == snakeY)
		{
			gameover = true;
		}
	}
	if (snakeX == fruitX && snakeY == fruitY)		//Progress tracking
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		otail++;
	}

}

int main()
{	
	int n;
	string name;
				//Main Menu
	cout << "Welcome to the Game!" << endl;
	cout << "Enter your name." << endl;
	cin >> name;
	cout << "1. Start the game." << endl;
	cout << "2. Check the high scores." << endl;
	cout << "3. Exit the game." << endl;
	cout << "Enter your choice" << endl;
	cin >> n;
	do
	{
		switch (n)
		{
		case 1:
		{
			score = 0;
			srand(time(0));
			startup();
			while (!gameover)
			{
				boundry();
				gameplay();
				logic();
				record();
				Sleep(10);
			}
			break;
		}

		case 2:			//Read High score
		{
			ifstream MyFile("Record.txt");
			if (!MyFile) 
			{ 
				cerr << "Error opening the file for reading!" << endl;
				return 1;
			}

			string line;
			cout << score;

			
			while (getline(MyFile, line))
			{
				cout << line << endl;
			}

			
			MyFile.close();

			return 0;
		}

		case 3:
		{
			gameover = true;
			exit(0);
		}
		default:
		{
			gameover = true;
			break;
		}
		}
		cout << "1. Start the game." << endl;
		cout << "2. Check the high scores." << endl;
		cout << "3. Exit the game." << endl;
		cout << "Enter your choice" << endl;
		cin >> n;
	} while (n!=3);
}