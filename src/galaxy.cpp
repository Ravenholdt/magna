#include "galaxy.h"

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