#include <limits>
#include <iostream>

#include "factories.h"

Factory::Factory(int type)
{
    size = 10;

    switch (type)
    {
    case (int)FactoryType::mine:
        inputMined[(int)Resources::metal] = 10;
        upkeep[(int)Resources::spareParts] = 5;
        output[(int)Resources::metal] = 10;
        break;
    case (int)FactoryType::infrastructure:
        inputStock[(int)Resources::metal] = 10;
        upkeep[(int)Resources::spareParts] = 5;
        output[(int)Resources::infrastructure] = 10;
        break;
    case (int)FactoryType::spareParts:
        inputStock[(int)Resources::metal] = 10;
        upkeep[(int)Resources::spareParts] = 5;
        output[(int)Resources::spareParts] = 10;
    };
};

Factory::Factory(){};
Factory::~Factory(){};

void Factory::tick(float planetMaterials[], float colonyStockpile[], float colonyDemand[], float *colonyCredits, float colonyPrice[])
{
    if (size <= 0)
    {
        size = 0;
        return;
    }

    float upkeepEfficiency = 1;
    float materialEfficiency = 1;
    float miningEfficiency = 1;

    float creditsStart = credits;
    
    // Calculate demand and upkeep

    credits -= creditsUpkeep;
    //std::cout << "Calculate demand" << std::endl;
    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        float required = 0;

        // Check demand and inform the colony
        required = (this->upkeep[i] + this->inputStock[i]) * size;
        colonyDemand[i] += required;

        if (required)
        {
            // Check supply of the factory and don't request more if not needed
            required = (required * daysOfStorage) - this->stockpile[i];
            if (required < 0) {required = 0;}

            // Check supply of the colony
            if (required > colonyStockpile[i]) {required = colonyStockpile[i];}

            // Transfer resourses from colony to factory.
            this->stockpile[i] += required;
            credits -= required * colonyPrice[i];

            colonyStockpile[i] -= required;
            *colonyCredits += required * colonyPrice[i];

            // Consume upkeep and penalise for lack of resourses.
            if (this->upkeep[i])
            {
                required = this->upkeep[i] * size;
                if (required > this->stockpile[i]) {required = this->stockpile[i];}
                upkeepEfficiency *= (required / upkeep[i]);
                this->stockpile[i] -= required;
            }
        }
    }

    // Calculate mining efficiency
    //std::cout << "Calculate mining efficiency" << std::endl;
    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        float required = 0;

        if (this->inputMined[i])
        {
            required = this->inputMined[i] * upkeepEfficiency * size;
            if (required > planetMaterials[i]) {required = planetMaterials[i];}
            float availability = required / this->inputMined[i];
            if (availability < miningEfficiency) {miningEfficiency = availability;}
        }
    }

    // Calculate production efficency
    //std::cout << "Calculate production efficiency" << std::endl;
    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        float required = 0;

        // Check material availability
        if (this->inputStock[i])
        {
            required = this->inputStock[i] * upkeepEfficiency * size;
            if (required > this->stockpile[i]) {required = this->stockpile[i];}
            
            float availability = required / this->stockpile[i];
            if (availability < materialEfficiency) {materialEfficiency = availability;}
        }
    }

    /*
    std::cout << "Upkeep Efficency: " << upkeepEfficency << std::endl;
    std::cout << "Mining Efficency: " << miningEfficency << std::endl;
    std::cout << "Material Efficency: " << materialEfficency << std::endl;
    */

    // Produce
    //std::cout << "Produce" << std::endl;
    this->efficiency = materialEfficiency * upkeepEfficiency * miningEfficiency;
    //std::cout << "Total Efficency: " << efficency << std::endl;
    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        float required = 0;

        // Mining
        if (this->inputMined[i])
        {
            required = this->inputMined[i] * efficiency * size;
            if (required > planetMaterials[i]) {required = planetMaterials[i];}
            planetMaterials[i] -= required;
        }

        // Consumption
        if (this->inputStock[i])
        {
            required = this->inputStock[i] * efficiency * size;
            if (required > this->stockpile[i]) {required = this->stockpile[i];}
            this->stockpile[i] -= required;
        }

        // Production
        if (output[i])
        {
            this->stockpile[i] += this->output[i] * efficiency * size;
            //std::cout << i << ": " << this->stockpile[i] << " (" << this->output[i] * efficency << ")" << std::endl;
        }
    }

    // Sell goods
    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        float required = 0;

        required = this->upkeep[i] + this->inputStock[i];
        required *= daysOfStorage;

        float surplus = stockpile[i] - required;
        
        // If surplus, sell
        if (surplus > 0)
        {
            colonyStockpile[i] += surplus;
            *colonyCredits -= surplus * colonyPrice[i];

            stockpile[i] -= surplus;
            credits += surplus * colonyPrice[i];
        }
    }

    // Calculate profits and expand
    float creditsEnd = credits;
    //if (!creditsStart) {creditsStart = 1e-20;}
    profits = creditsEnd - creditsStart;

    profitability = (profitability + profits) / 2;

    size += (int)(profitability/2) / (size * 10);
    if (size < 0) {size = 0;}
};

void Factory::print()
{
    std::cout << "Size: " << size << " (" << efficiency << ")"<< std::endl;
    std::cout << "Credits: " << credits << "(" << profitability << ", " << profits << ")" << std::endl;
    std::cout << "Factory Stockpile: ";

    for(int i = 0; i < (int)Resources::indexLast; i++)
    {
        std::cout << stockpile[i] << ", ";
    }

    std::cout << std::endl;
};