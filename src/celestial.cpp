#include <iostream>
#include <math.h>

#include "celestial.h"

int planetOffset = 0;

Celestial::Celestial(){}
Celestial::~Celestial(){}

Celestial::Celestial(int id, int parent, float distance, float mass, float radius, CelestialType type)
{ 
    this->id = id;
    this->parent = parent;
    this->distance = distance;
    this->mass = mass;
    this->radius = radius;
    this->type = type;

    if (parent) 
    {
        this->orbitalPeriod = calculateOrbitalPeriod(this->getParent()->mass, distance);
        this->system = this->getParent()->getSystem()->getId();
    }

    this->environment.gravity = this->gravity();
};

Celestial* Celestial::getParent() { return galaxy.getCelestial(this->parent); }
System* Celestial::getSystem() { return galaxy.getSystem(this->system); }

void Celestial::addChild(int child)
{
    this->childs.push_back(child);
}

void Celestial::addToParent()
{
    if (this->parent) 
    {
        this->getParent()->addChild(this->id);
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

void Celestial::getPosInSystem(float* x, float* y, long long int time)
{
    *x = 0;
    *y = 0;

    int current = this->id;
    int parent;

    double pi = 3.14159265;
    double placeInOrbit;
    while (galaxy.getCelestial(current)->parent)
    {   
        parent = galaxy.getCelestial(current)->parent;

        placeInOrbit = (time % galaxy.getCelestial(current)->orbitalPeriod) / (float)galaxy.getCelestial(current)->orbitalPeriod;

        *x = (cos(placeInOrbit * 360. * (pi/180.)) * (double)galaxy.getCelestial(current)->distance);
        *y = (sin(placeInOrbit * 360. * (pi/180.)) * (double)galaxy.getCelestial(current)->distance);

        current = parent;
    }
}

void Celestial::tick(long long int time)
{
    //std::cout << "Celestial: " << this->id << std::endl;

    if (!this->colonies.size()) return; // If planet is inactive, return.

    //float infrastructureRequirment = this->population - this->infrastructure;
    //this->demand[(int)Resources::infrastructure] += infrastructureRequirment;
    //float ratio = this->stockpileMaterials[(int)Resources::infrastructure] / infrastructureRequirment;
    //if (ratio > 0) 
    //{ 
    //    float buildInfrastructure = infrastructureRequirment * ratio;
    //    this->stockpileMaterials[(int)Resources::infrastructure] -= buildInfrastructure;
    //    this->infrastructure += buildInfrastructure;
    //}

    for (int i = 0; i < this->colonies.size(); i++)
    {
        galaxy.getColony(this->colonies[i])->tick(time);
    }

//    for (int i = 0; i < (int)Resources::indexLast; i++)
//    {
//        this->priceMod[i] *= this->demand[i] / this->stockpileMaterials[i];
//        if (this->stockpileMaterials[i] <= 0) { this->priceMod[i] = this->priceBase[i] * 100; }
//        if (this->priceMod[i] < (this->priceBase[i] / 100)) { this->priceMod[i] = this->priceBase[i] / 100; }
//        if (this->priceMod[i] > (this->priceBase[i] * 100)) { this->priceMod[i] = this->priceBase[i] * 100; }
//
//        std::cout << "Price " << i << ": " << this->priceMod[i] * this->priceBase[i] << std::endl;
//    }
};

void Celestial::tickDaily()
{
    if (this->childs.size())
    {
        for (int i = 0; i < this->childs.size(); i++)
        {
            galaxy.getCelestial(this->childs[i])->tickDaily();
        }
    }

    if (this->colonies.size())
    {
        for (int i = 0; i < this->colonies.size(); i++)
        {
            galaxy.getColony(this->colonies[i])->tickDaily();
        }
    }
}

void Celestial::tickMonthly()
{
    if (!this->colonies.size()) return; // If planet is inactive, return.

    for (int i = 0; i < this->colonies.size(); i++)
    {
        galaxy.getColony(this->colonies[i])->tickMonthly();
    }
}