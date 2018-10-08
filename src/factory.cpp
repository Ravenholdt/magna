#include "factory.h"

using namespace std;

FactoryHandler::FactoryHandler()
{
    // Initiate all the factories
    for (int i = 0; i < nrOfFactories; i++)
    {
        switch(i)
        {
            case farm:
                factoryArray[i] = new Factory();
                factoryArray[i]->output->resources[Resource::food] = 1;
                factoryArray[i]->upkeep->resources[Resource::wealth] = 0.1;
                break;

            case mine:
                factoryArray[i] = new Factory();
                factoryArray[i]->mine = true;
                factoryArray[i]->planetary_input->resources[Resource::metal] = 1;
                factoryArray[i]->output->resources[Resource::metal] = 1;
                factoryArray[i]->upkeep->resources[Resource::wealth] = 0.2;
                break;

            case factory:
                factoryArray[i] = new Factory();
                factoryArray[i]->input->resources[Resource::metal] = 1;
                factoryArray[i]->output->resources[Resource::goods] = 1;
                factoryArray[i]->upkeep->resources[Resource::wealth] = 0.2;
                break;
        }
    }
};
FactoryHandler::~FactoryHandler(){};

/*
The Produce function works by first checking how much resource each factory require.
It then compares this to the avalible stockpile and ranson the resources so that all factories can operate.
*/
void FactoryHandler::produce(Resource* consumedResources, Resource* producedResources, Resource* efficiency, Resource* planetResources)
//void FactoryHandler::produce(Resource** planetResourcePack)
{
    // Produce
    for (int i = 0; i < nrOfFactories; i++)
    {
        float tmpEfficiency = 1;
        float upkeepEfficiency = 1;

        Resource* expenses = new Resource(); // The value of all consumed resources to run the factory
        Resource* income = new Resource(); // The value of all outputs from the factory

        // Calculate the efficiency for the current factory depending on the avalible resources, using the lowest efficiency per factory.
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            // Check if the new efficiency is lower than the last.
            if (factoryArray[i]->input->resources[n] > 0 && efficiency->resources[n] < tmpEfficiency)
            {
                tmpEfficiency = efficiency->resources[n];
            }
        }

        // Calculate the efficiency for the current factory depending on the avalible resources, using the lowest efficiency per factory.
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            // Check if the new efficiency is lower than the last.
            if (factoryArray[i]->upkeep->resources[n] > 0 && efficiency->resources[n] < upkeepEfficiency)
            {
                upkeepEfficiency = efficiency->resources[n];
            }
        }
        //upkeepEfficiency = 0.1;

        tmpEfficiency *= upkeepEfficiency;
        printf("Efficiency[%d]: %0.4f, %0.4f\n", i, tmpEfficiency, upkeepEfficiency);

        tmpEfficiency *= factoryArray[i]->amount;

        // Calculate the production output and input depending on the efficiency.
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            expenses->resources[n] += factoryArray[i]->input->resources[n] * tmpEfficiency + factoryArray[i]->upkeep->resources[n] * factoryArray[i]->amount * upkeepEfficiency;
            consumedResources->resources[n] += factoryArray[i]->input->resources[n] * tmpEfficiency + factoryArray[i]->upkeep->resources[n] * factoryArray[i]->amount * upkeepEfficiency;

            if (factoryArray[i]->mine)
            {
                // If factory is a mine and wants the resource from a planet
                income->resources[n] += factoryArray[i]->output->resources[n] * planetResources->resources[n] * tmpEfficiency;
                producedResources->resources[n] += factoryArray[i]->output->resources[n] * planetResources->resources[n] * tmpEfficiency;
            } else {
                income->resources[n] += factoryArray[i]->output->resources[n] * tmpEfficiency;
                producedResources->resources[n] += factoryArray[i]->output->resources[n] * tmpEfficiency;
            }
        }

        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            factoryArray[i]->expenses->resources[n] = expenses->resources[n];
            factoryArray[i]->income->resources[n] = income->resources[n];
        }
    }
}

// Factories requestion materials.
void FactoryHandler::request(Resource* requestedResources)
{
    for (int i = 0; i < nrOfFactories; i++)
    {
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            requestedResources->resources[n] += factoryArray[i]->input->resources[n] * factoryArray[i]->amount;
            requestedResources->resources[n] += factoryArray[i]->upkeep->resources[n] * factoryArray[i]->amount;
        }
    }
}

void FactoryHandler::calculateProfit(Resource* marketPrice)
{
    for (int i = 0; i < nrOfFactories; i++)
    {
        float income = 0;
        float expenses = 0;
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            income += factoryArray[i]->income->resources[n] * marketPrice->resources[n];
            expenses += factoryArray[i]->expenses->resources[n] * marketPrice->resources[n];
        }

        float profit = income / expenses;
        // Just in case both is 0
        if (expenses == 0 || profit > 10){profit = 10;}
        if (income == 0 || profit < 0.1){profit = 0.1;}

        printf("Profit[%d]: %0.4f\n", i, profit);

        factoryArray[i]->amount *= ((profit - 1) / 10) + 1;
        printf("Factories[%d]: %0.4f\n", i, factoryArray[i]->amount);
    }
}

Factory::Factory()
{
    this->profit = 0;
    this->amount = 1;
};