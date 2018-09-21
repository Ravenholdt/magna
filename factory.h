#pragma once

#include <map>

#include "resource.h"

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
    float request[nrOfResources];
    float output[nrOfResources];

    float factoryArray[nrOfFactories];
    FactoryHandler();
    ~FactoryHandler();

    void produce(float planetResources[nrOfResources]);
};

//class Factory