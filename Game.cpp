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


void Labyrinth::Game::Initialize(int inputLevel, bool inputCross, int inputGold)
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
	level->number = inputLevel;
	level->Load(levelsNames[inputLevel-1]);
	char personSymbol;
	int lookRadius = 0;
	bool cross = inputCross;
	bool string = 0;
	int gold = inputGold;
	in = ifstream("Person.txt");


	in >> tmp >> personSymbol >> tmp >> lookRadius;

	person = new Labyrinth::Person(level->personStartLine, level->personStartColumn, lookRadius, level, personSymbol, cross, string, gold);

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

void endText(int gold)
{
	system("cls");
	cout << endl << endl << "\t\t\t  God helped you. You're free now. " << endl << endl;
		
	if (gold != 0)
	{
		cout << "\t\t\t  You have collected " << gold << " gold coins." << endl << endl
			<< "\t\tBut what will you do with your freedom and this money?" << endl << endl
			<< "\t\t\t\tGoodbye, righteous man." << endl;
	}
	else
	{
		cout << "\t\t\tBut what will you do with your freedom ?" << endl << endl
			<< "\t\t\t       Goodbye, righteous man." << endl;
	}

	_getch();
	system("cls");
		cout << "\n\n\n"<< "\t \t \t \t  [ENDGAME]" << endl << endl
			<< "\t \t  Saint-Petersburg -- Kuznetck -- Zapolyarny" << endl << endl
		<< "\t \t \t \t Bonch, 2020." << endl;

	_getch();
}


void Labyrinth::Game::Run()
{
	srand(time(NULL));

	int coderes, checkOpenChest = 0, command = 0;
	bool mirror = 0, lockChest = 1;

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

		if (lockChest && level->IsChest(person->line, person->column))
		{
			cout << endl << "This is the chest! Click 'O' to open it" << endl;
			while (checkOpenChest != 'o')
			{

				checkOpenChest = getchar();
				
			}
			checkOpenChest = 42;
			int tmpGold = 0;
			int rTreasure = 1+rand() % 5;
			switch (rTreasure)
			{
			case 1: tmpGold = 1 + rand() % 100;
					person->gold += tmpGold;
					cout << "There are a few gold coins," << tmpGold << " to be exact" << endl;
					_getch();
					break;

			case 2:
				if (!person->cross)
				{
					cout << "It's a Trap! The poison gas suffocates you and your body falls without life." << endl;
					_getch();
					system("cls");
					cout << "\n\n\t\t\tGood-bye, sinner. You tried." << endl;
					_getch();
					command = 'm';
					break;
				}
				else
				{
					cout << endl << "The crucifix saves your life and breaks down.Now everything is in your hands." << endl;
					_getch();
					person->cross = false;
				}
			
			case 3: cout << "There is a crucifix in the chest. It will save you from one trap." << endl;
					_getch();
					person->cross = true;
					break;
			
			case 4: cout << "This is a mirror. You find a mirror.Looking into it, you realize that the walls" << endl
					     << "in your reflection change and you find yourself in a completely different room." << endl; 
					mirror = 1; _getch(); break;
			case 5: cout << endl << "You found Ariadne's thread. Now you can mark your way."; 
					person->string = 1; _getch();
					break;
			
			default:
				break;
			}
			lockChest = 0;
		}

		if (mirror || level->IsExit(person->line, person->column))
		{
			if (levelsCount > level->number)
			{
				system("cls");
				if (!mirror)
					coderes = code();
				if (mirror || coderes == 0)
				{
					mirror = 0;
					person->string = 0;
					lockChest = 1;
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
				int gold = person->gold;
				endText(gold);
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