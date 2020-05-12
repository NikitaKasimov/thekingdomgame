#include "Game.h"
#include <fstream>
#include <iostream>
#include <conio.h>
	

using namespace Labyrinth;
using namespace std;


int loadSave()
{
	int level;
	ifstream in("Save.txt");

	char tmp[256] = {0};

	in >> tmp >> level;
	in.close();
	return level;
}

void control()
{
	system("cls");
	cout << endl << "\n\t\t\t\tGo up - 'W'\n\n\t\t\t\tGo left - 'A'\n\n\t\t\t\tGo right - 'D'\n\n\t\t\t\tGo down - 'S'" << endl
		<< endl << "\n\t\t\t\tTo save - 'B'"
		<< endl << "\n\t\t\t\tGo to menu - 'M'";
	_getch();
}

void about()
{
	system("cls");
	cout << "\t \t \t This game is called <Kingdom>." << endl << endl
		<< "\t \t \t The main goal of the game is to escape from  the \n \t \t \tcellars of the Evil King`s castle." << endl << endl << endl
		<< "\t \t \t The game was developed by Nikita Kasimov, \n \t \t \t Polina Povaibo and Ilya Matveev." << endl
		<< "\t \t \t Special for D.Y. Fedorov." << endl << endl
		<< "\t \t \t Saint Petersburg, Bonch, 2020." << endl << endl << endl << endl
		<< "\t \t \t Put any button to return to Main Menu" << endl;

	_getch();

}

void mainmenu()
{
	system("cls");
	cout << "\t\t\t  _______________________" << endl
		 << "\t\t\t  |                     |" << endl
		 << "\t\t\t  |   The Kingdom Game  |" << endl
		 << "\t\t\t  |                     |" << endl
	 	 << "\t\t\t  |     [Main Menu]     |" << endl
		 << "\t\t\t  |                     |" << endl
		 << "\t\t\t  |   1 - New Game      |" << endl
		 << "\t\t\t  |   2 - Load Save     |" << endl
		 << "\t\t\t  |   3 - About Game    |" << endl
		 << "\t\t\t  |   4 - Control Game  |" << endl
		 << "\t\t\t  |   5 - Exit          |" << endl
		 << "\t\t\t  |                     |" << endl
		 << "\t\t\t  -----------------------" << endl;
}

int main()
{
	int n, level = 1;
	while (true)
	{
		level = 1;
		mainmenu();
		cin >> n;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (n)
		{
		case 1:
			 break;
		case 2:
			level = loadSave(); break;
		case 3:
			about();
			break;
		case 4:
			control();
			continue;
		case 5:
			exit(0);  break;
		default:
			continue;
		}
		Game game;

		game.Initialize(level);
		game.Run();
	}
	return 0;
}


