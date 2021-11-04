#pragma once
#ifndef Snake_h
#define Snake_h

//;ibraries for this header 
#include <iostream>
#include <Windows.h>
#include <vector>

//define variables to help make the game board
#define width 50
#define height 50

using namespace std;

//declare the class for the player object
class SnakePlayer
{
public:
	SnakePlayer();
	SnakePlayer(COORD pos, int velocity);  // declare constructors
	~SnakePlayer();							//declare destructor

	void Increase();
	void Move();
	void Direction();

	bool Collide();
	bool Eat(COORD food);

	vector<COORD> get_body;

	COORD get_pos();

private:
	COORD pos;
	int velocity;
	int direct;
	int len;
	vector<COORD> body;

};


#endif // !Snake_h
