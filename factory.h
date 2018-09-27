#pragma once

#include <map>

#include "resource.h"

using namespace std;

enum FactoryType
{
    farm,
    mine,
    factory,

    nrOfFactories
};

class FactoryHandler
{
public:
    //float request[nrOfResources];
    //float output[nrOfResources];

    //float factoryArray[nrOfFactories];
    FactoryHandler();
    ~FactoryHandler();

    //void produce(float planetResources[nrOfResources]);
    void produce(Resource* planetResources);
};


class Factory
{
protected:
public:
    int id;
    
    //Resource input = new Resource();
    map<int, float> input = {};
    map<int, float> output = {};

    map<int, float> require = {};
    map<int, float> upkeep = {};

    Factory();
    ~Factory();
};
