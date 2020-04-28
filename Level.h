namespace Labyrinth
{
	class Person;

	class Level
	{
	public:

		char floorSymbol;
		char wallSymbol;
		char exitSymbol;


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


		Level();

		void Load(char * filename);
		void Print();

		bool CanMove(int line, int column);
		bool IsExit(int line, int column);
		~Level();

	};
}