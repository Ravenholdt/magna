#include "generateSol.h"

void generateTerra(int sun)
{
    int p, m, c;
    p = galaxy.getCelestial(sun)->newChild(1.474e11, 5.97e24, 6.371e6, CelestialType::planet); // Earth
		galaxy.getCelestial(p)->name = "Terra";
		galaxy.getCelestial(p)->environment.habitability = 1;
		galaxy.getCelestial(p)->environment.atmosphere = 1;
		galaxy.getCelestial(p)->planetaryMaterials[(int)Resources::industrialMetals] = 1e0;
		galaxy.getCelestial(p)->planetaryMaterials[(int)Resources::rareMetals] = 1e-3;
		galaxy.getCelestial(p)->planetaryMaterials[(int)Resources::preciousMetals] = 1e-9;

	c = galaxy.getCelestial(p)->newColony(p); // Humanity
		galaxy.getColony(c)->population.amount = 1000000000;
		//galaxy.getColony(c)->factoriesNum = 20000020;
		galaxy.getColony(c)->stockpileMaterials[(int)Resources::mine] = 500020;
		galaxy.getColony(c)->production[(int)Resources::consumerGoods] = 500010;
		galaxy.getColony(c)->infrastructure = galaxy.getColony(c)->population.amount;

    m = galaxy.getCelestial(p)->newChild(3.85e8, 7.3459e22, 1.7374e6, CelestialType::moon); // Moon
		galaxy.getCelestial(m)->name = "Luna";
        galaxy.getCelestial(m)->environment.habitability = 0.2;
		galaxy.getCelestial(m)->planetaryMaterials[(int)Resources::industrialMetals] = 1e0;
		galaxy.getCelestial(m)->planetaryMaterials[(int)Resources::rareMetals] = 1e-3;
		galaxy.getCelestial(m)->planetaryMaterials[(int)Resources::preciousMetals] = 1e-9;

	c = galaxy.getCelestial(m)->newColony(m); // Lunar Base
		galaxy.getColony(c)->population.amount = 1000;

}

int generateSol()
{
	int sol = galaxy.newSystem();
	int sun = galaxy.systems[sol].star;

	int p, m;
	p = galaxy.celestials[sun].newChild(6.76e10, 3.301e23, 2.44e6, CelestialType::planet); // Mercury
		galaxy.getCelestial(p)->name = "Mercury";
        galaxy.getCelestial(p)->environment.habitability = 0.1;

	p = galaxy.celestials[sun].newChild(1.078e11, 4.867e24, 6.05e6, CelestialType::planet); // Venus
		galaxy.getCelestial(p)->name = "Venus";
        galaxy.getCelestial(p)->environment.habitability = 0.001;

    generateTerra(sun);

	p = galaxy.celestials[sun].newChild(2.207e11, 6.417e23, 2.39e6, CelestialType::planet); // Mars
		galaxy.getCelestial(p)->name = "Mars";
        galaxy.getCelestial(p)->environment.habitability = 0.2;
    {
        m = galaxy.getCelestial(p)->newChild(9.4e6, 1.072e16, 1.108e4, CelestialType::moon); // Phobos
			galaxy.getCelestial(m)->name = "Phobos";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
        m = galaxy.getCelestial(p)->newChild(2.3e7, 1.5e15, 6.2e3, CelestialType::moon); // Deimos
			galaxy.getCelestial(m)->name = "Deimos";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
    }

	p = galaxy.celestials[sun].newChild(7.636e11, 1.898e27, 6.995e7, CelestialType::planet); // Jupiter
		galaxy.getCelestial(p)->name = "Jupiter";
        galaxy.getCelestial(p)->environment.habitability = 0;
	{
		m = galaxy.getCelestial(p)->newChild(4.217e8, 8.931938e22, 1.8216e6, CelestialType::moon); // Io
			galaxy.getCelestial(m)->name = "Io";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
		m = galaxy.getCelestial(p)->newChild(6.709e8, 4.799844e22, 1.5608e6, CelestialType::moon); // Europa
			galaxy.getCelestial(m)->name = "Europa";
            galaxy.getCelestial(m)->environment.habitability = 0.2;
		m = galaxy.getCelestial(p)->newChild(1.0716e9, 1.4819e23, 2.6341e6, CelestialType::moon); // Ganymede
			galaxy.getCelestial(m)->name = "Ganymede";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
		m = galaxy.getCelestial(p)->newChild(1.8827e9, 1.0759e23, 2.41e6, CelestialType::moon); // Callisto
			galaxy.getCelestial(m)->name = "Callisto";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
	}

	p = galaxy.celestials[sun].newChild(1.495e12, 5.683e26, 5.83e7, CelestialType::planet); // Saturn
		galaxy.getCelestial(p)->name = "Saturn";
        galaxy.getCelestial(p)->environment.habitability = 0;
	{
        m = galaxy.getCelestial(p)->newChild(1.85539e8, 3.7493e19, 1.982e5, CelestialType::moon); // Minmas
			galaxy.getCelestial(m)->name = "Minmas";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
        m = galaxy.getCelestial(p)->newChild(2.37948e8, 1.08022e20, 2.521e5, CelestialType::moon); // Enceladus
			galaxy.getCelestial(m)->name = "Enceladus";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
        m = galaxy.getCelestial(p)->newChild(2.94619e8, 6.17449e20, 5.311e5, CelestialType::moon); // Tethys
			galaxy.getCelestial(m)->name = "Tethys";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
        m = galaxy.getCelestial(p)->newChild(3.77396e8, 1.095452e21, 1.1228e6, CelestialType::moon); // Dione
			galaxy.getCelestial(m)->name = "Dione";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
        m = galaxy.getCelestial(p)->newChild(5.27108e8, 2.306518e21, 7.638e5, CelestialType::moon); // Rhea
			galaxy.getCelestial(m)->name = "Rhea";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
        m = galaxy.getCelestial(p)->newChild(1.221870e9, 1.3452e23, 2.57473e6, CelestialType::moon); // Titan
			galaxy.getCelestial(m)->name = "Titan";
            galaxy.getCelestial(m)->environment.habitability = 0.01;
			galaxy.getCelestial(p)->environment.atmosphere = 1.45;
        m = galaxy.getCelestial(p)->newChild(3.560820e9, 1.805635e21, 1.4690e6, CelestialType::moon); // Iapetus
			galaxy.getCelestial(m)->name = "Iapetus";
            galaxy.getCelestial(m)->environment.habitability = 0.1;
	}

	p = galaxy.celestials[sun].newChild(2.958e12, 8.681e25, 2.536e7, CelestialType::planet); // Uranus
		galaxy.getCelestial(p)->name = "Uranus";
        galaxy.getCelestial(p)->environment.habitability = 0;

	p = galaxy.celestials[sun].newChild(4.477e12, 1.024e26, 2.46e7, CelestialType::planet); // Nepture
		galaxy.getCelestial(p)->name = "Neptune";
        galaxy.getCelestial(p)->environment.habitability = 0;

	return sol;
}