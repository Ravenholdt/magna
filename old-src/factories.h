#pragma once

#include "resources.h"

enum class FactoryType{mine, infrastructure, spareParts, indexLast};

class Factory
{

    public:
    int size = 0;
    float profits = 0;
    float profitability = 0;
    float efficiency = 0;
    float credits = 0;
    float creditsUpkeep = 0;

    int daysOfStorage = 10;

    float expansionCost[(int)Resources::indexLast]={0};

    float stockpile[(int)Resources::indexLast]={0};
    float upkeep[(int)Resources::indexLast]={0};

    float inputMined[(int)Resources::indexLast]={0};
    float inputStock[(int)Resources::indexLast]={0};
    float output[(int)Resources::indexLast]={0};

    Factory(int type);
    Factory();
    ~Factory();

    void tick(float planetMaterials[], float colonyStockpile[], float colonyDemand[], float *colonyCredits, float colonyPrice[]);
    void print();
};