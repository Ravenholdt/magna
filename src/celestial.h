#include <string>

#include "resource.h"
#include "factory.h"

class Celestial
{
protected:
    int id;

    // The stockpile symbolize the resources that have been extracted and are accessible.
    Resource* stockpile = new Resource();
    // The stockpile demand is used to check the balance of avalible resources to simulate a market economy.
    Resource* stockpileDemand = new Resource();
    // The market price increase during a shortage of resources and decrease during a surplus.
    Resource* marketPrice = new Resource(1);
    // The celestial resources symbolize the materials still in the planet waiting to be extracted.
    Resource* celestialResources = new Resource();

public:
    string name;
    float population;

    FactoryHandler* factories = new FactoryHandler();

    Celestial();
    ~Celestial();

    Resource* getStockpile();
    Resource* getResources();
    Resource* getStockpileDemand();
    Resource* getMarketPrice();

    //For when a function requires all resource pointers.
    Resource **getResourcePack();

    void calculateDemand(Resource* requestedResources);
    void produce(Resource* consumedResources, Resource* producedResources, Resource* efficiency);
    void consume(Resource* consumedResources, Resource* efficiency = new Resource(1));
    void calculateNewMarketPrice(Resource* stockpileDemand);
    void tick();
};