#include <Food.h>

SnakeFood::SnakeFood()
{
}

SnakeFood::~SnakeFood()
{
}

void SnakeFood::MakeFood()
{
	FoodPos.X = (rand() % width - 3) + 1;
	FoodPos.Y = (rand() % height - 3) + 1;
}

COORD SnakeFood::get_pos()
{
	return FoodPos;
}