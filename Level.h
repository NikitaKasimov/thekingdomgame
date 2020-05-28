namespace Labyrinth
{
	class Person;

	class Level
	{
	public:

		char floorSymbol;
		char wallSymbol;
		char exitSymbol;
		char chestSymbol;

		int number;
		int width;
		int height;
		char** area;
		bool** areaMask;

		Person* person;

		int personStartLine;
		int personStartColumn;

		int exitLine;
		int exitColumn;

		int chestLine;
		int chestColumn;

		Level();

		void Load(char * filename);
		void Print();

		bool CanMove(int line, int column);
		bool IsExit(int line, int column);
		bool IsChest(int line, int column);
		~Level();

	};
}