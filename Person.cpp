#include "Person.h"
#include "Level.h"

Labyrinth::Person::Person(int line, int column, int lookRadius, Labyrinth::Level* level, char symbol)
{
	this->line = line;
	this->column = column;
	this->level = level;
	this->lookRadius = lookRadius;
	this->symbol = symbol;

}

void Labyrinth::Person::Move(int command)
{
	switch (command)
	{
	case 'w':
		if (level->CanMove(line - 1, column)) --line;
		break; 

	case 'a':
		if (level->CanMove(line, column - 1)) --column;
		break;

	case 's':
		if (level->CanMove(line + 1, column)) ++line;

		break;

	case 'd':
		if (level->CanMove(line, column + 1)) ++column;

		break;
	default:
		break;
	}

}


void Labyrinth::Person::LookAround()
{
	for (int i = 0; i < level->height; i++)
	{
		for (int j = 0; j < level->width; j++)
		{
			if ((line - i)*(line - i) + (column - j)*(column - j) <= lookRadius*lookRadius)
			{
				level->areaMask[i][j] = true;
			}
		}
	}
}