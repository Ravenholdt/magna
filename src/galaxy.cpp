
#include <iostream>
#include <iterator>

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

int Galaxy::newColony(int parent)
{
    colonyCounter++;
    this->colonies[colonyCounter] = Colony(colonyCounter, parent, 0);
    return colonyCounter;
}

int Galaxy::newShip()
{
    shipCounter++;
    return shipCounter;
}

void Galaxy::tick()
{
    this->time += 1000;
    std::cout << "Time: " << time << std::endl;
    
    for (std::pair<int, Celestial> element : this->celestials) {
        element.second.tick(time);
    }
}