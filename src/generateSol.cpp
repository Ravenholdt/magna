#include "generateSol.h"

void generateTerra(int sun)
{
    int p, m, c;
    p = galaxy.celestials[sun].newChild(1.474e11, 5.97e24, 6.371e6, CelestialType::planet); // Earth
		galaxy.celestials[p].name = "Terra";
		galaxy.celestials[p].habitability = 1;
		galaxy.celestials[p].atmosphere = 1;

	c = galaxy.celestials[p].newColony(p); // Humanity
		galaxy.colonies[c].population = 10000000000;
		galaxy.colonies[c].factoriesNum = 10000;
		galaxy.colonies[c].stockpileMaterials[(int)Resources::mine] = 10;
		galaxy.colonies[c].production[(int)Resources::metal] = 100;
		galaxy.colonies[c].infrastructure = galaxy.colonies[c].population;

    m = galaxy.celestials[p].newChild(3.85e8, 7.3459e22, 1.7374e6, CelestialType::moon); // Moon
		galaxy.celestials[m].name = "Luna";
	c = galaxy.celestials[m].newColony(m); // Lunar Base
		galaxy.colonies[c].population = 10000;
}

int generateSol()
{
	int sol = galaxy.newSystem();
	int sun = galaxy.systems[sol].star;

	int p, m;
	p = galaxy.celestials[sun].newChild(6.76e10, 3.301e23, 2.44e6, CelestialType::planet); // Mercury
		galaxy.celestials[p].name = "Mercery";
		galaxy.celestials[p].atmosphere = 0;

	p = galaxy.celestials[sun].newChild(1.078e11, 4.867e24, 6.05e6, CelestialType::planet); // Venus
		galaxy.celestials[p].name = "Venus";

    generateTerra(sun);

	p = galaxy.celestials[sun].newChild(2.207e11, 6.417e23, 2.39e6, CelestialType::planet); // Mars
		galaxy.celestials[p].name = "Mars";
    {
        m = galaxy.celestials[p].newChild(9.4e6, 1.072e16, 1.108e4, CelestialType::moon); // Phobos
			galaxy.celestials[m].name = "Phobos";
			galaxy.celestials[p].atmosphere = 0;
        m = galaxy.celestials[p].newChild(2.3e7, 1.5e15, 6.2e3, CelestialType::moon); // Deimos
			galaxy.celestials[m].name = "Deimos";
			galaxy.celestials[p].atmosphere = 0;
    }

	p = galaxy.celestials[sun].newChild(7.636e11, 1.898e27, 6.995e7, CelestialType::planet); // Jupiter
		galaxy.celestials[p].name = "Jupiter";

	p = galaxy.celestials[sun].newChild(1.495e12, 5.683e26, 5.83e7, CelestialType::planet); // Saturn
		galaxy.celestials[p].name = "Saturn";

	p = galaxy.celestials[sun].newChild(2.958e12, 8.681e25, 2.536e7, CelestialType::planet); // Uranus
		galaxy.celestials[p].name = "Uranus";

	p = galaxy.celestials[sun].newChild(4.477e12, 1.024e26, 2.46e7, CelestialType::planet); // Nepture
		galaxy.celestials[p].name = "Neptune";

	return sol;
}