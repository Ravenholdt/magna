#include <iostream>

#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
	initiateRecipes();

	int sol = generateSol();

	shipinitialization();

	for (int i = 1; i <= galaxy.celestials.size(); i++)
	{
		std::cout << galaxy.celestials[i].parent << " <- " << galaxy.celestials[i].getID() << std::endl;
	}

	std::cout << "Begin" << std::endl;

	// GUI
	if (argc == 1)
	{
		gui(window);
	}

	// No GUI
	else
	{
		while (true)
		{
			getchar();
			galaxy.tick(DAY);

			std::cout << "Day: " << galaxy.time / (float)DAY << std::endl;
		}
	}

	return 0;
}