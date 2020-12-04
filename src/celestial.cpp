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
        this->priceBase[i] = 1;
        this->priceMod[i] = 1;
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

    if (!(this->population || this->colonies.size())) return; // If planet is inactive, return.

    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        this->demand[i] = 0;
    }

    float infrastructureRequirment = this->population - this->infrastructure;
    this->demand[(int)Resources::infrastructure] += infrastructureRequirment;
    float ratio = this->stockpileMaterials[(int)Resources::infrastructure] / infrastructureRequirment;
    if (ratio > 0) 
    { 
        float buildInfrastructure = infrastructureRequirment * ratio;
        this->stockpileMaterials[(int)Resources::infrastructure] -= buildInfrastructure;
        this->infrastructure += buildInfrastructure;
    }

    for (int i = 0; i < this->colonies.size(); i++)
    {
        galaxy.colonies[this->colonies[i]].tick(time);
    }

    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        this->priceBase[i] = 1;
    }

    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        this->priceMod[i] *= this->demand[i] / this->stockpileMaterials[i];
        if (this->stockpileMaterials[i] <= 0) { this->priceMod[i] = this->priceBase[i] * 100; }
        if (this->priceMod[i] < (this->priceBase[i] / 100)) { this->priceMod[i] = this->priceBase[i] / 100; }
        if (this->priceMod[i] > (this->priceBase[i] * 100)) { this->priceMod[i] = this->priceBase[i] * 100; }

        std::cout << "Price " << i << ": " << this->priceMod[i] * this->priceBase[i] << std::endl;
    }
    std::cout << this->infrastructure << std::endl;
};