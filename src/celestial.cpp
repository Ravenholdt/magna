#include "celestial.h"

Celestial::Celestial()
{ 
    celestialResources->resources[Resource::metal] = 0.5; 
    population = 10;
    stockpile->resources[Resource::wealth] = population;
};
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

// Returns the total ammount of resources required by the planet.
void Celestial::calculateDemand(Resource* requestedResources)
{
    factories->request(requestedResources);
    this->consume(requestedResources);
}

// The factories consume and produce.
void Celestial::produce(Resource* consumedResources, Resource* producedResources, Resource* efficiency)
{
    this->factories->produce(consumedResources, producedResources, efficiency, this->celestialResources);
    this->consume(consumedResources, producedResources, efficiency);
}

// The population and planet consume resources.
void Celestial::consume(Resource* consumedResources, Resource* producedResources, Resource* efficiency)
{
    producedResources->resources[Resource::wealth] += population;
    consumedResources->resources[Resource::food] += population * efficiency->resources[Resource::food];
    consumedResources->resources[Resource::metal] += population * efficiency->resources[Resource::metal];

    printf("TESTING: %.3f\n", efficiency->resources[Resource::food]);
}

// Calculate price
void Celestial::calculateNewMarketPrice(Resource* stockpileDemand)
{
    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        if (i != Resource::wealth)
        {
            float avalibility = stockpileDemand->resources[i] / this->stockpile->resources[i];
            if (stockpileDemand->resources[i] == this->stockpile->resources[i])
            {
                avalibility = 1;
            } else {
                if (stockpileDemand->resources[i] == 0) { avalibility = 0.1; }
                if (this->stockpile->resources[i] == 0){ avalibility = 10; }
                if (avalibility > 2){ avalibility = 2; }
                if (avalibility < 0.5) { avalibility = 0.5; }
            }
            this->marketPrice->resources[i] *= avalibility;
        }
    }
}

void Celestial::tick()
{
    // Get demand for resources
    Resource* requestedResources = new Resource();
    this->calculateDemand(requestedResources);

    printf("WEALTH EFF: %.3f..%.3f\n", this->stockpile->resources[Resource::wealth], requestedResources->resources[Resource::wealth]);

    // Calculate the efficiency of production
    Resource* efficiency = new Resource();
    // Check if all the required materials are avalible
    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        float tmpEfficiency = this->stockpile->resources[i] / requestedResources->resources[i];
        if (tmpEfficiency > 1) {tmpEfficiency = 1;}
        efficiency->resources[i] = tmpEfficiency;
    }
    //efficiency->resources[Resource::wealth] = 0.1;

    //printf("WEALTH EFF: %.3f\n", efficiency->resources[Resource::wealth]);

    // Produce resources from factories
    Resource* consumedResources = new Resource();
    Resource* producedResources = new Resource();
    this->produce(consumedResources, producedResources, efficiency);

    // Add the produced resources to the stockpile
    consumedResources->removeFrom(this->stockpile);
    producedResources->addTo(this->stockpile);

    // Calculate the new market price
    this->calculateNewMarketPrice(requestedResources);

    this->factories->calculateProfit(marketPrice);
}