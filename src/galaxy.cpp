#include "galaxy.h"
#include <iostream>

Galaxy galaxy;

int Galaxy::newCelestial(int parent, float distance, float mass, float radius, CelestialType type)
{
    celestialCounter++;
    this->celestials[celestialCounter] = Celestial(celestialCounter, parent, distance, mass, radius, type);
    this->celestials[celestialCounter].addToParent();
    return celestialCounter;
}

int Galaxy::newSystem()
{
    systemCounter++;
    this->systems[systemCounter] = System(systemCounter);
    return systemCounter;
}

int Galaxy::newColony()
{
    colonyCounter++;
    this->colonies[colonyCounter] = Colony();
}

void Galaxy::tick()
{
    this->time += 1000;
    std::cout << "Time: " << time << std::endl;
}