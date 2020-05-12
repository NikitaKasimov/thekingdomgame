#include "Level.h"
#include "Person.h"
#include <iostream>
#include <fstream>

using namespace std;

Labyrinth::Level::Level()
{
	floorSymbol = wallSymbol = exitSymbol = 0;
	number = width = height = personStartColumn = personStartLine = exitColumn = exitLine =  0;
	area = 0;
	areaMask = 0;
	person = 0;

}


bool Labyrinth::Level::CanMove(int line, int column)
{
	return area[line][column] != wallSymbol;

}

bool Labyrinth::Level::IsExit(int line, int column)
{
	return line == exitLine && column == exitColumn;

}

void Labyrinth::Level::Print()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (areaMask[i][j])
			{

				if (i == person->line && j == person->column)
				{
					cout << person->symbol;
				}
				else if (IsExit(i, j))
				{
					cout << exitSymbol;
				}
				else
				{
					cout << area[i][j];
				}
			}
			else
			{
				cout << ' ';
			}
		}
		cout << endl;
	}
	cout << endl << "Room " << number << endl << endl;
}

void Labyrinth::Level::Load(char* filename)
{
	ifstream in(filename);
	char tmp[256] = { 0 };

	in >> tmp >> floorSymbol
		>> tmp >> wallSymbol
		>> tmp >> exitSymbol
		>> tmp >> personStartLine
		>> tmp >> personStartColumn
		>> tmp >> exitLine
		>> tmp >> exitColumn;

	if (area != nullptr)
	{
		for (int i = 0; i < height; ++i)
		{
			delete[] area[i];
			delete[] areaMask[i];
		}
		delete[] area;
		delete[] areaMask;
	}

	in >> tmp >> height
		>> tmp >> width;

	area = new char *[height];
	areaMask = new bool *[height];

	for (int i = 0; i < height; ++i)
	{
		area[i] = new char[width];
		areaMask[i] = new bool[width];
	}

	in.get();

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			/*char s = in.peek();
			if (s != '#' && s != '-')
			{
				__debugbreak();
			}*/
			area[i][j] = in.get();
			areaMask[i][j] = false;
		}
		in.get();
	}
	in.close();
}


Labyrinth::Level::~Level()
{
	if (area != 0)
	{
		for (int i = 0; i < height; ++i)
		{
			delete[] area[i];
			delete[] areaMask[i];
		}
		delete[] area;
		delete[] areaMask;
	}

}
