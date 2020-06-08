#pragma once

#include <string>

#include "resources.h"
#include "factories.h"

class Colony
{
    public:
    std::string name;
    float population;
    float credits;

    int daysOfStorage = 10;

    float colonyStockpile[(int)Resources::indexLast]={0};
    float colonySupply[(int)Resources::indexLast]={0};
    float colonyDemand[(int)Resources::indexLast]={0};

    float colonyPrice[(int)Resources::indexLast];

    Factory factories[(int)FactoryType::indexLast];
    float productionProfits[(int)FactoryType::indexLast];

    Colony();
    ~Colony();
    void tick(float materials[]);
    void print();
};