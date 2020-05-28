namespace Labyrinth
{
	class Level;

	class Person
	{
	public:

		int lookRadius;
		int line;
		int column;
		
		Level* level;

		char symbol;

		bool cross;
		bool string;
		int gold;

		Person(int line, int column, int lookRadius, Level* level, char symbol, bool cross, bool string, int gold);

		void Save();
		void Move(int command);
		void LookAround();
	};
}