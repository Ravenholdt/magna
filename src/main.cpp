#include <iostream>

#include "main.h"
#include "galaxy.h"

#include "ships.h"

using namespace std;

int createSol()
{
    int sol = galaxy.newSystem();
    int sun = galaxy.systems[sol].star;

    int p;
    p = galaxy.celestials[sun].newChild(5e10, 6e24, 6.4e6, CelestialType::planet); // Mercury
    p = galaxy.celestials[sun].newChild(1e11, 6e24, 6.4e6, CelestialType::planet); // Venus
    p = galaxy.celestials[sun].newChild(1.5e11, 6e24, 6.4e6, CelestialType::planet); // Earth
        galaxy.celestials[p].population = 10000000000;
        galaxy.celestials[p].newColony(p); // Humanity
        m = galaxy.celestials[p].newChild(4e8, 1e10, 1.7e6, CelestialType::moon); // Moon
        galaxy.celestials[m].population = 10000;
        galaxy.celestials[m].newColony(m); // Humanity
    p = galaxy.celestials[sun].newChild(2.1e11, 6e24, 6.4e6, CelestialType::planet); // Mars
        galaxy.celestials[p].newChild(9.4e6, 1e16, 1.1e4, CelestialType::moon); // Phobos
        galaxy.celestials[p].newChild(2.3e7, 1.5e15, 6.2e3, CelestialType::moon); // Deimos
    p = galaxy.celestials[sun].newChild(7.7e11, 6e24, 6.4e6, CelestialType::planet); // Jupiter
    p = galaxy.celestials[sun].newChild(1.5e12, 6e24, 6.4e6, CelestialType::planet); // Saturn
    p = galaxy.celestials[sun].newChild(3e12, 6e24, 6.4e6, CelestialType::planet); // Uranus
    p = galaxy.celestials[sun].newChild(4.5e12, 6e24, 6.4e6, CelestialType::planet); // Nepture

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
        galaxy.tick();
    }

    return 0;
}