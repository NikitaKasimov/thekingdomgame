#include "Game.h"
#include "Person.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include <conio.h>

using namespace std;

Labyrinth::Game::Game()
{
	level = 0;
	person = 0;
	levelsNames = 0;
	levelsCount = 0;
}


void Labyrinth::Game::Initialize()
{

	ifstream in("Levels.txt");
	int filesNameMaxLenght=0;

	char tmp[256] = { 0 };

	in >> tmp >> levelsCount >> tmp >> filesNameMaxLenght;

	levelsNames = new char *[levelsCount];

	for (int i = 0; i < levelsCount; i++)
		levelsNames[i] = new char[filesNameMaxLenght];

	in.get();

	for (int i = 0; i < levelsCount; i++)
		in.getline(levelsNames[i], filesNameMaxLenght);

	in.close();

	level = new Labyrinth::Level();
	level->number = 1;
	level->Load(levelsNames[0]);
	char personSymbol;
	int lookRadius = 0;

	in = ifstream("Person.txt");


	in >> tmp >> personSymbol >> tmp >> lookRadius;

	person = new Labyrinth::Person(level->personStartLine, level->personStartColumn, 
													lookRadius, level, personSymbol);

	level->person = person; 

}


void Labyrinth::Game::Run()
{

	int command = 0;
	while (command != 'q')
	{
		system("cls");
		person->LookAround();
		level->Print();
		command = _getch();
		person->Move(command);

		if (level->IsExit(person->line, person->column))
		{
			if (levelsCount > level->number)
			{
				level->Load(levelsNames[level->number]);
				++(level->number);
				person->line = level->personStartLine;
				person->column = level->personStartColumn;
			}
			
			else
			{
				cout << endl << "It is your win!";
				system("pause");
				break;
			}
		}
	}

}





Labyrinth::Game::~Game()
{
	if (levelsCount > 0)
	{
		for (int i = 0; i < levelsCount; i++)
			delete[] levelsNames[i];
		delete[] levelsNames;
	}
}