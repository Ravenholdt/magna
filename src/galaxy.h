#pragma once

#include "celestial.h"
#include "system.h"

#include <map>

class Galaxy
{
private:
    int celestialCounter = 0;
    int systemCounter = 0;
    int colonyCounter = 0;
public:
    std::map<int, Celestial> celestials;
    std::map<int, System> systems;
    std::map<int, Colony> colonies;

    //Galaxy(/* args */);
    //~Galaxy();

    long long int time = 0;

    int newCelestial(int parent, float distance, float mass, float radius, CelestialType type);
    int newSystem();
    int newColony();
    
    void tick();
};

extern Galaxy galaxy;