#include <iostream>
#include <math.h>

#include "galaxy.h"

int planetOffset = 0;

Celestial::Celestial(){}
Celestial::~Celestial(){}

Celestial::Celestial(int id, int parent, float distance, float mass, float radius, CelestialType type)
{ 
    this->id = id;
    this->parent = parent;
    this->mass = mass;
    this->distance = distance;
    this->type = type;

    if (parent) 
    {
        this->orbitalPeriod = 2.0 * 3.14 * sqrt( pow(distance, 3) / (galaxy.celestials[this->parent].mass * 6.674e-11) );
    }

    for(int i = 0; i < (int)Resources::indexRaw; i++)
    {
        this->planetaryMaterials[i] = 0.5;
    }
};

void Celestial::addChild(int child)
{
    this->childs.push_back(child);
}

void Celestial::addToParent()
{
    if (this->parent) 
    {
        galaxy.celestials[this->parent].addChild(this->id);
    }
}

int Celestial::newChild(float distance, float mass, float radius, CelestialType type)
{
    return galaxy.newCelestial(this->id, distance, mass, radius, type);
}

int Celestial::newColony(int parent)
{
    int c = galaxy.newColony(parent);
    this->colonies.push_back(c);
    
    return c;
}

void Celestial::tick(long long int time)
{
    //std::cout << "Celestial: " << this->id << std::endl;

    for (int i = 0; i < this->colonies.size(); i++)
    {
        galaxy.colonies[this->colonies[i]].tick(time);
    }
};