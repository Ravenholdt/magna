#include <iostream>
#include <math.h>

#include "galaxy.h"

int planetOffset = 0;

Celestial::Celestial(){}
Celestial::~Celestial(){}

Celestial::Celestial(int id, int parent, float distance, float mass, float radius)
{ 
    this->id = id;
    this->parent = parent;
    this->mass = mass;
    this->distance = distance;

    if (parent) this->orbitalPeriod = 2.0 * 3.14 * sqrt( pow(distance, 3) / (galaxy.celestials[parent].mass * 6.674e-11) );

    for(int i = 0; i < (int)Resources::indexRaw; i++)
    {
        this->planetaryMaterials[i] = 0.5;
    }
};

void Celestial::addChild(int child)
{
    //std::cout << "Adding child...";
    this->childs.push_back(child);
    //std::cout << " Done!" << std::endl;
}

void Celestial::addToParent()
{
    //std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    if (this->parent) 
    {
        //std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        galaxy.celestials[parent].addChild(this->id);
    }
    //std::cout << __FILE__ << ": " << __LINE__ << std::endl;
}

int Celestial::newChild(float distance, float mass, float radius)
{
    return galaxy.newCelestial(this->id, distance, mass, radius);
}

sf::Vector2f Celestial::orbitToPos(long long int time)
{
    if (!this->parent) return sf::Vector2f(0,0);

    float orb = (float)((time + this->offset) % this->orbitalPeriod) / this->orbitalPeriod;
    float rads = orb * 6.28;
    if (rads <= 0) rads = 1e-10;
    sf::Vector2f pos(cos(rads) * this->distance, sin(rads) * this->distance);

    return pos;
}

void Celestial::tick()
{
};