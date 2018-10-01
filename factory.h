#pragma once

#include <map>

#include "resource.h"

using namespace std;

class Factory
{
protected:

public:

    int id;
    //Resource input = new Resource();
    //map<int, float> input = {};
    Resource* input = new Resource();
    //map<int, float> output = {};
    Resource* output = new Resource();

    //map<int, float> require = {};
    Resource* require = new Resource();
    //map<int, float> upkeep = {};
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
    void produce(Resource* planetResources);
};
