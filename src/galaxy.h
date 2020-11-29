#pragma once

#include <map>

#include "system.h"
#include "celestial.h"
#include "colony.h"

class Galaxy
{
private:
    int celestialCounter = 0;
    int systemCounter = 0;
    int colonyCounter = 0;

    int shipCounter = 0;
public:
    std::map<int, System> systems;
    std::map<int, Celestial> celestials;
    std::map<int, Colony> colonies;

    //Galaxy(/* args */);
    //~Galaxy();

    long long int time = 0;

    int newCelestial(int parent, float distance, float mass, float radius, CelestialType type);
    int newSystem();
    int newColony(int parent);

    int newShip();
    
    void tick();
};

extern Galaxy galaxy;