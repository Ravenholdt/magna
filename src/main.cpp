#include <iostream>

#include "main.h"
#include "galaxy.h"
#include "algorithms.h"
#include "generateSol.h"

#include "ships.h"

using namespace std;

int main()
{
	initiateRecipes();

	int sol = generateSol();

	shipinitialization();

	for (int i = 1; i <= galaxy.celestials.size(); i++)
	{
		std::cout << galaxy.celestials[i].parent << " <- " << galaxy.celestials[i].getID() << std::endl;
	}

	std::cout << "Begin" << std::endl;

	while (true)
	{
		getchar();
		galaxy.tick(DAY);

		std::cout << "Day: " << galaxy.time / (float)DAY << std::endl;
	}

	return 0;
}