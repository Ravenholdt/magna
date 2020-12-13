#include "generateSol.h"

void generateTerra(int sun)
{
    int p, m, c;
    p = galaxy.celestials[sun].newChild(1.474e11, 5.97e24, 6.371e6, CelestialType::planet); // Earth
		galaxy.celestials[p].name = "Terra";
		galaxy.celestials[p].environment.habitability = 1;
		galaxy.celestials[p].environment.atmosphere = 1;
		galaxy.celestials[p].planetaryMaterials[(int)Resources::industrialMetals] = 1e0;
		galaxy.celestials[p].planetaryMaterials[(int)Resources::rareMetals] = 1e-3;
		galaxy.celestials[p].planetaryMaterials[(int)Resources::preciousMetals] = 1e-9;

	c = galaxy.celestials[p].newColony(p); // Humanity
		galaxy.colonies[c].population = 1000000000;
		//galaxy.colonies[c].factoriesNum = 20000020;
		galaxy.colonies[c].stockpileMaterials[(int)Resources::mine] = 500020;
		galaxy.colonies[c].production[(int)Resources::consumerGoods] = 500010;
		galaxy.colonies[c].infrastructure = galaxy.colonies[c].population;

    m = galaxy.celestials[p].newChild(3.85e8, 7.3459e22, 1.7374e6, CelestialType::moon); // Moon
		galaxy.celestials[m].name = "Luna";
        galaxy.celestials[m].environment.habitability = 0.2;
		galaxy.celestials[m].planetaryMaterials[(int)Resources::industrialMetals] = 1e0;
		galaxy.celestials[m].planetaryMaterials[(int)Resources::rareMetals] = 1e-3;
		galaxy.celestials[m].planetaryMaterials[(int)Resources::preciousMetals] = 1e-9;

	c = galaxy.celestials[m].newColony(m); // Lunar Base
		galaxy.colonies[c].population = 1000;

}

int generateSol()
{
	int sol = galaxy.newSystem();
	int sun = galaxy.systems[sol].star;

	int p, m;
	p = galaxy.celestials[sun].newChild(6.76e10, 3.301e23, 2.44e6, CelestialType::planet); // Mercury
		galaxy.celestials[p].name = "Mercury";
        galaxy.celestials[p].environment.habitability = 0.1;

	p = galaxy.celestials[sun].newChild(1.078e11, 4.867e24, 6.05e6, CelestialType::planet); // Venus
		galaxy.celestials[p].name = "Venus";
        galaxy.celestials[p].environment.habitability = 0.001;

    generateTerra(sun);

	p = galaxy.celestials[sun].newChild(2.207e11, 6.417e23, 2.39e6, CelestialType::planet); // Mars
		galaxy.celestials[p].name = "Mars";
        galaxy.celestials[p].environment.habitability = 0.2;
    {
        m = galaxy.celestials[p].newChild(9.4e6, 1.072e16, 1.108e4, CelestialType::moon); // Phobos
			galaxy.celestials[m].name = "Phobos";
            galaxy.celestials[m].environment.habitability = 0.1;
        m = galaxy.celestials[p].newChild(2.3e7, 1.5e15, 6.2e3, CelestialType::moon); // Deimos
			galaxy.celestials[m].name = "Deimos";
            galaxy.celestials[m].environment.habitability = 0.1;
    }

	p = galaxy.celestials[sun].newChild(7.636e11, 1.898e27, 6.995e7, CelestialType::planet); // Jupiter
		galaxy.celestials[p].name = "Jupiter";
        galaxy.celestials[p].environment.habitability = 0;
	{
		m = galaxy.celestials[p].newChild(4.217e8, 8.931938e22, 1.8216e6, CelestialType::moon); // Io
			galaxy.celestials[m].name = "Io";
            galaxy.celestials[m].environment.habitability = 0.1;
		m = galaxy.celestials[p].newChild(6.709e8, 4.799844e22, 1.5608e6, CelestialType::moon); // Europa
			galaxy.celestials[m].name = "Europa";
            galaxy.celestials[m].environment.habitability = 0.2;
		m = galaxy.celestials[p].newChild(1.0716e9, 1.4819e23, 2.6341e6, CelestialType::moon); // Ganymede
			galaxy.celestials[m].name = "Ganymede";
            galaxy.celestials[m].environment.habitability = 0.1;
		m = galaxy.celestials[p].newChild(1.8827e9, 1.0759e23, 2.41e6, CelestialType::moon); // Callisto
			galaxy.celestials[m].name = "Callisto";
            galaxy.celestials[m].environment.habitability = 0.1;
	}

	p = galaxy.celestials[sun].newChild(1.495e12, 5.683e26, 5.83e7, CelestialType::planet); // Saturn
		galaxy.celestials[p].name = "Saturn";
        galaxy.celestials[p].environment.habitability = 0;
	{
        m = galaxy.celestials[p].newChild(1.85539e8, 3.7493e19, 1.982e5, CelestialType::moon); // Minmas
			galaxy.celestials[m].name = "Minmas";
            galaxy.celestials[m].environment.habitability = 0.1;
        m = galaxy.celestials[p].newChild(2.37948e8, 1.08022e20, 2.521e5, CelestialType::moon); // Enceladus
			galaxy.celestials[m].name = "Enceladus";
            galaxy.celestials[m].environment.habitability = 0.1;
        m = galaxy.celestials[p].newChild(2.94619e8, 6.17449e20, 5.311e5, CelestialType::moon); // Tethys
			galaxy.celestials[m].name = "Tethys";
            galaxy.celestials[m].environment.habitability = 0.1;
        m = galaxy.celestials[p].newChild(3.77396e8, 1.095452e21, 1.1228e6, CelestialType::moon); // Dione
			galaxy.celestials[m].name = "Dione";
            galaxy.celestials[m].environment.habitability = 0.1;
        m = galaxy.celestials[p].newChild(5.27108e8, 2.306518e21, 7.638e5, CelestialType::moon); // Rhea
			galaxy.celestials[m].name = "Rhea";
            galaxy.celestials[m].environment.habitability = 0.1;
        m = galaxy.celestials[p].newChild(1.221870e9, 1.3452e23, 2.57473e6, CelestialType::moon); // Titan
			galaxy.celestials[m].name = "Titan";
            galaxy.celestials[m].environment.habitability = 0.01;
			galaxy.celestials[p].environment.atmosphere = 1.45;
        m = galaxy.celestials[p].newChild(3.560820e9, 1.805635e21, 1.4690e6, CelestialType::moon); // Iapetus
			galaxy.celestials[m].name = "Iapetus";
            galaxy.celestials[m].environment.habitability = 0.1;
	}

	p = galaxy.celestials[sun].newChild(2.958e12, 8.681e25, 2.536e7, CelestialType::planet); // Uranus
		galaxy.celestials[p].name = "Uranus";
        galaxy.celestials[p].environment.habitability = 0;

	p = galaxy.celestials[sun].newChild(4.477e12, 1.024e26, 2.46e7, CelestialType::planet); // Nepture
		galaxy.celestials[p].name = "Neptune";
        galaxy.celestials[p].environment.habitability = 0;

	return sol;
}