#include "Snake.h"

// basic constructor definition
SnakePlayer::SnakePlayer()
{
}

//define constructor used that can interact
SnakePlayer::SnakePlayer(COORD pos, int velocity)
{
	this->pos = pos;
	this->velocity = velocity;

	direct = 'n';
	length = 1;

	body.push_back(pos);
}

//destructor define
SnakePlayer::~SnakePlayer()
{
}

//always check direction to move
void SnakePlayer::Direction(char drct)
{
	this->direct = drct;
}

//function to increase snake length
void SnakePlayer::Increase()
{
	length++;
}

//returns vector to keep track of orientation and movement
vector<COORD> SnakePlayer::get_body()
{
	return vector<COORD>();
}

//returns coordinates to get position of snake
COORD SnakePlayer::get_pos()
{
	return pos;
}

//controls moving and works to detect body size
void SnakePlayer::Move()
{
	switch (direct)
	{
	case 'u': pos.Y -= velocity; break;
	case 'd': pos.Y += velocity; break;
	case 'l': pos.X -= velocity; break;
	case 'r': pos.X += velocity; break;
	}

	body.push_back(pos);

	if (body.size() > length)
	{
		body.erase(body.begin());
	}
}

//collision detector
bool SnakePlayer::Collide()
{
	if (pos.X < 1 || pos.X > width - 2 || pos.Y < 1 || pos.Y > height - 2)
	{
		return true;
	}

	for (int i = 0; i < length - 1; i++)
	{
		if (pos.X == body[i].X && pos.Y == body[i].Y)
		{
			return true;
		}
	}

	return false;
}

//eat food function definition
bool SnakePlayer::Eat(COORD food)
{
	if (pos.X == food.X && pos.Y == food.Y)
	{
		//tells program that food has been eaten and to create a new one
		return true;
	}

	//makes it so the new food stays until eaten
	return false;
}