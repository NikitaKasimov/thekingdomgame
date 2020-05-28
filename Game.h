namespace Labyrinth
{

	class Person;
	class Level;


	class Game
	{
		public:
			char** levelsNames;
			Person* person;
			Level* level;
			int levelsCount;


			Game();

			void Initialize(int inputlevel, bool inputCross, int inputGold);
			void Run();

			~Game();
	};
}