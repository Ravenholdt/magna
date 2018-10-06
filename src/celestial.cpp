#include "celestial.h"

Celestial::Celestial(){ celestialResources->resources[Resource::metal] = 0.5; };
Celestial::~Celestial(){};

Resource* Celestial::getStockpile(){ return this->stockpile; }
Resource* Celestial::getResources(){ return this->celestialResources; }
Resource* Celestial::getStockpileDemand(){ return this->stockpileDemand; }
Resource* Celestial::getMarketPrice(){ return this->marketPrice; }

//For when a function requires all resource pointers.
Resource **Celestial::getResourcePack()
{
    static Resource* resArray[] = {this->stockpile, this->celestialResources, this->stockpileDemand, this->marketPrice};
    return resArray;
}