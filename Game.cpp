#include "Game.h"
#include "Person.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <limits>
using namespace std;

Labyrinth::Game::Game()
{
	level = 0;
	person = 0;
	levelsNames = 0;
	levelsCount = 0;
}


void Labyrinth::Game::Initialize(int inputlevel)
{

	ifstream in("Levels.txt");
	int filesNameMaxLenght = 0;

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
	level->number = inputlevel;
	level->Load(levelsNames[inputlevel-1]);
	char personSymbol;
	int lookRadius = 0;

	in = ifstream("Person.txt");


	in >> tmp >> personSymbol >> tmp >> lookRadius;

	person = new Labyrinth::Person(level->personStartLine, level->personStartColumn,
		lookRadius, level, personSymbol);

	level->person = person;

}

int code()
{

	srand(time(NULL));

	int digMassOne[5] = { 0 }, digMassTwo[5] = { -1 };


	cout << "\t\t   This is a door with a combination lock." << endl 
		 << "\t\tRemember the numbers and put them in ascending" <<endl 
		 << "\t\t     order and you can go further." << endl << endl<<"\t\t\t";

	for (int i = 0; i < 5; i++)
	{
		digMassOne[i] = rand() % 10;
		cout << " [" << digMassOne[i] << "] ";
	}
	cout << endl;


	int temp;


	for (int i = 0; i < 5 - 1; i++) {
		for (int j = 0; j < 5 - i - 1; j++) {
			if (digMassOne[j] > digMassOne[j + 1]) {
				temp = digMassOne[j];
				digMassOne[j] = digMassOne[j + 1];
				digMassOne[j + 1] = temp;
			}
		}
	}


	cout << endl << "\t\t    Press any button, if you are ready!" << endl;
	_getch();
	system("cls");

	cout << "\t\t\tEnter the numbers faster!" << endl;

	for (int i = 0; i < 5; i++)
	{

		cin >> digMassTwo[i];

	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (digMassTwo[0] < 0)
	{
		cout << "\t\t  You are not worthy. Return to the previous level!" << endl;
		_getch();
		return -1;
	}

	int count = 0;

	for (int i = 0; i < 5; i++)
	{

		if (digMassOne[i] == digMassTwo[i])
			++count;

	}


	if (count == 5)
	{
		cout << "\t\t    Go to next room!" << endl;
		_getch();
		return 0;
	}
	else
	{
		cout << "\t\t  You are not worthy. Return to the previous level!" << endl;
		_getch();
		return -1;
	}


}

void startText()
{
	system("cls");
	cout << endl << endl << " \t\t\tYou wake up on the floor of a damp cellar." << endl
		<< "\t\t\tThere's only a Bible in your pocket." << endl << endl
		<< "\t \t \t Pray and run. Run for freedom." << endl;

	_getch();
	system("cls");
	cout << endl << "\n\t\t\t\tGo up - 'W'\n\n\t\t\t\tGo left - 'A'\n\n\t\t\t\tGo right - 'D'\n\n\t\t\t\tGo down - 'S'" << endl
		<< endl << "\n\t\t\t\tTo save - 'B'"
		<< endl << "\n\t\t\t\tGo to menu - 'M'";
	_getch();
	system("cls");
}

void endText()
{
	system("cls");
	cout << endl << endl << "\t\t\t  God helped you. You're free now." << endl << endl
		<< "\t\t\tBut what will you do with your freedom?" << endl << endl
		<< "\t\t\t\tGoodbye, righteous man." << endl;
	_getch();
	system("cls");
		cout << "\n\n\n"<< "\t \t \t \t  [ENDGAME]" << endl << endl
		<< "\t \t \t Saint Petersburg, Bonch, 2020." << endl;

	_getch();
}


void Labyrinth::Game::Run()
{

	int coderes, command = 0;
	if (level->number == 1)
		startText();
	while (command != 'm')
	{
		system("cls");
		if (levelsCount < level->number)
		{
			cout << "Your soul is corrupted. Good-bye, sinner." << endl;
			_getch();
			command = 'm';
			break;
		}
		
		person->LookAround();
		level->Print();
		command = _getch();
		person->Move(command);

		if (level->IsExit(person->line, person->column))
		{
			if (levelsCount > level->number)
			{
				system("cls");
				coderes = code();
				if (coderes == 0)
				{
					level->Load(levelsNames[level->number]);
					++(level->number);
					person->line = level->personStartLine;
					person->column = level->personStartColumn;
				}
				else
				{
					level->Load(levelsNames[level->number-1]);
					person->line = level->personStartLine;
					person->column = level->personStartColumn;
				}
			}

			else
			{
				endText();
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