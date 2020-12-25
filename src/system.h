#pragma once

#include <string>

#include "galaxy.h"
#include "resources.h"

class Celestial;

class System
{
private:
    int id;
public:
    int star;

    float supply[(int)Resources::indexLast];
    float demand[(int)Resources::indexLast];
    
    System();
    System(int id);
    //~System();
    int getId() { return this->id; }
    Celestial* getStar();

    void addCelestial(int parent, float mass, float distance);

    void tick(long long int time);
    void tickDaily();
};
