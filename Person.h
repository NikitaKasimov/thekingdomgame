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

		Person(int line, int column, int lookRadius, Level* level, char symbol);

		void Save();
		void Move(int command);
		void LookAround();
	};
}