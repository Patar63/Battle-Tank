//external libraries for a timer, formatting, and score tracking
#include <iostream>
#include <ctime>
#include <conio.h>

//include header files
#include "Snake.h"
#include "Food.h"

//make width and height to define screen
#define width 50
#define height 50

using namespace std;

//declare global variables
int Score;

//create player         //use {} to work with COORD type
SnakePlayer Player({ width / 2, height / 2 }, 1);
//create first food
SnakeFood Food;

//create the game board
void GameBrd()
{
	//get coordinates from snake and food from their functions
	COORD Player_pos = Player.get_pos();
	COORD Food_pos = Food.get_pos();
	vector<COORD> Player_body = Player.get_body();

	//create score board display text
	cout << "Score = " << Score << "\n";

	//large series of 'if' and 'for' loops used to accurately show text on screen.
	for (int i = 0; i < height; i++)
	{
		cout << "\t\t#";

		for (int j = 0; j < width - 2; j++)
		{
			if (i == 0 || i == height - 1)
			{
				cout << '#';
			}
			else if (i == Player_pos.Y && (j + 1) == Player_pos.X)
			{
				cout << '0';
			}
			else if (i == Food_pos.Y && (j + 1) == Food_pos.X)
			{
				cout << '@';
			}
			else
			{
				bool piece = false;
				for (int k = 0; k < (Player_body.size() - 1); k++)
				{
					if (i == Player_body[k].Y && (j + 1) == Player_body[k].X)
					{
						cout << 'o';
						piece = true;
						break;
					}
				}

				if (piece == false)
				{
					cout << ' ';
				}
			}
		}

		cout << "#\n";
	}
}


int main()
{
	//create needed variables and define
	Score = 0;
	srand(time(NULL));
	char GameOver = false;

	Food.MakeFood();

	while (GameOver == false)
	{
		//call the game board
		GameBrd();

		//assign controls for up, down, left, and right using kbhit and getch
		if (kbhit)
		{
			switch (getch())
			{
			case 'w': Player.Direction('u'); 
				break;
			case 'a': Player.Direction('l');
				break;
			case 's': Player.Direction('d');
				break;
			case 'd': Player.Direction('r');
				break;
			}
		}

		//check if a collision occurs and trigger game over
		if (Player.Collide())
		{
			GameOver = true;
		}
		//Checks if the player ate a food
		if (Player.Eat(Food.get_pos()))
		{
			//make a new food
			Food.MakeFood();
			//make player bigger
			Player.Increase();
			//increase score
			Score = Score + 1;
		}

		Player.Move();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	}
}