#pragma once

#ifndef Food_h
#define Food_h

#include <Windows.h>
#include <cstdio>

//define variables to help make the game board
#define width 50
#define height 50

class SnakeFood
{
public:
	//declare public functions for food object
	SnakeFood();
	~SnakeFood();

	void MakeFood();

	COORD get_pos();

private:

	COORD FoodPos;

};

#endif // !Food_h
