#pragma once

#include "celestial.h"
#include "system.h"

#include <map>

class Galaxy
{
private:
    int celestialCounter = 0;
    int systemCounter = 0;
public:
    std::map<int, Celestial> celestials;
    std::map<int, System> systems;

    //Galaxy(/* args */);
    //~Galaxy();

    int newCelestial(int parent, float distance, float mass, float radius);
    int newSystem();
};

extern Galaxy galaxy;