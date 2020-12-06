#include <iostream>

#include "main.h"
#include "galaxy.h"

#include "ships.h"

using namespace std;

int createSol()
{
    int sol = galaxy.newSystem();
    int sun = galaxy.systems[sol].star;

    int p, m, c;
    p = galaxy.celestials[sun].newChild(6.76e10, 3.301e23, 2.44e6, CelestialType::planet); // Mercury
    p = galaxy.celestials[sun].newChild(1.078e11, 4.867e24, 6.05e6, CelestialType::planet); // Venus
    p = galaxy.celestials[sun].newChild(1.474e11, 5.97e24, 6.371e6, CelestialType::planet); // Earth
        c = galaxy.celestials[p].newColony(p); // Humanity
        galaxy.colonies[c].population = 10000000000;
        m = galaxy.celestials[p].newChild(3.85e8, 7.3459e22, 1.7374e6, CelestialType::moon); // Moon
        c = galaxy.celestials[m].newColony(m); // Lunar Base
        galaxy.colonies[c].population = 10000;
    p = galaxy.celestials[sun].newChild(2.207e11, 6.417e23, 2.39e6, CelestialType::planet); // Mars
        galaxy.celestials[p].newChild(9.4e6, 1.072e16, 1.108e4, CelestialType::moon); // Phobos
        galaxy.celestials[p].newChild(2.3e7, 1.5e15, 6.2e3, CelestialType::moon); // Deimos
    p = galaxy.celestials[sun].newChild(7.636e11, 1.898e27, 6.995e7, CelestialType::planet); // Jupiter
    p = galaxy.celestials[sun].newChild(1.495e12, 5.683e26, 5.83e7, CelestialType::planet); // Saturn
    p = galaxy.celestials[sun].newChild(2.958e12, 8.681e25, 2.536e7, CelestialType::planet); // Uranus
    p = galaxy.celestials[sun].newChild(4.477e12, 1.024e26, 2.46e7, CelestialType::planet); // Nepture

    return sol;
}

int main()
{
    initiateRecipes();

    int sol = createSol();

    shipinitialization();

    for (int i = 1 ; i <= galaxy.celestials.size() ; i++)
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