
#include <iostream>
#include <iterator>

#include "galaxy.h"
#include "ships.h"

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

int Galaxy::newFleet() 
{
	fleetCounter++;
	return fleetCounter;
}

int Galaxy::newShipDesign() {
	shipDesignCounter++;
	return shipDesignCounter;
}

float Galaxy::distance(int source, int target)
{
    float sx, sy, tx, ty;
    float dx, dy;

    galaxy.celestials[source].getPosInSystem(&sx, &sy, galaxy.time);
    galaxy.celestials[target].getPosInSystem(&tx, &ty, galaxy.time);

    dx = abs(sx - tx);
    dy = abs(sy - ty);

    return sqrt(pow(dx, 2)+pow(dy, 2));
}

void Galaxy::tick(long long int timeStep)
{
    this->time += timeStep;
    std::cout << "Time: " << time << std::endl;
    
    for (std::pair<int, Celestial> element : this->celestials) {
        element.second.tick(time);
    }
	arrivalcheck();
	
}