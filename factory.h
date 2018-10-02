#pragma once

#include <map>

#include "resource.h"

using namespace std;

class Factory
{
protected:

public:

    int id;

    // Required input from the planetary stockpile
    Resource* input = new Resource();
    // Input mined from the planet
    Resource* planetary_input = new Resource();
    // Output to the planetary stockpile
    Resource* output = new Resource();

    // Requided materials for the factory to operate, not to be consumed.
    Resource* require = new Resource();
    // Materials consumed no matter how much is produced.
    Resource* upkeep = new Resource();

    Factory();
    ~Factory();
};

class FactoryHandler
{
public:

    enum FactoryType
    {
        farm,
        mine,
        factory,

        nrOfFactories
    };

    //float request[nrOfResources];
    Resource* efficiency = new Resource();
    Resource* efficiency_input = new Resource();
    Resource* efficiency_output = new Resource();
    //float output[nrOfResources];
    Resource* output = new Resource();

    //float factoryArray[nrOfFactories];
    Factory* factoryArray[nrOfFactories];
    FactoryHandler();
    ~FactoryHandler();

    //void produce(float planetResources[nrOfResources]);
    void produce(Resource* planetStockpile);
};
