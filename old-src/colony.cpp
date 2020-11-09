#include "colony.h"

#include <iostream>

Colony::Colony()
{
    for (int i = 0; i < (int)FactoryType::indexLast; i++)
    {
        std::cout << "Created factory" << std::endl;
        factories[i] = Factory(i);
    }

    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        colonyPrice[i] = 1;
    }

    colonyStockpile[(int)Resources::spareParts] = 200;
};
Colony::~Colony(){};

void Colony::tick(float planetMaterials[])
{
    // Reset demand calculaton
    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        colonyDemand[i] = 0;
        colonySupply[i] = colonyStockpile[i];
    }

    // Calculate resourses for factories
    for (int i = 0; i < (int)FactoryType::indexLast; i++)
    {
        //std::cout << "Factory: " << i << std::endl;
        factories[i].tick(planetMaterials, this->colonyStockpile, this->colonyDemand, &credits, this->colonyPrice);
    }

    // Calculate price from supply and demand
    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        float priceFactor = 0;
        if (colonySupply[i])
        {
            priceFactor = (colonyDemand[i] * daysOfStorage) / colonySupply[i];
        }
        else
        {
            priceFactor = 1 + (colonyDemand[i] * daysOfStorage);
        }

        if (priceFactor > 1.1) {priceFactor = 1.1;}
        if (priceFactor < 0.9) {priceFactor = 0.9;}

        colonyPrice[i] *= priceFactor;
        if (colonyPrice[i] < 0.01) {colonyPrice[i] = 0.01;}
        if (colonyPrice[i] > 1e+20) {colonyPrice[i] = 1e+20;}
    }
};

void Colony::print()
{
    std::cout << "Colony Credits: " << credits << std::endl;
    std::cout << "Colony Stockpile: ";

    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        std::cout << colonyStockpile[i] << ", ";
    }

    std::cout << std::endl;

    std::cout << "Colony Price: ";

    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        std::cout << colonyPrice[i] << ", ";
    }

    std::cout << std::endl;

    // Calculate resourses for factories
    for (int i = 0; i < (int)FactoryType::indexLast; i++)
    {
        std::cout << "Factory: " << i << std::endl;
        factories[i].print();
    }
};