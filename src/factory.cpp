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
                factoryArray[farm] = new Factory();
                factoryArray[farm]->output->resources[Resource::food] = 1;
                break;

            case mine:
                factoryArray[mine] = new Factory();
                factoryArray[mine]->mine = true;
                factoryArray[mine]->planetary_input->resources[Resource::metal] = 1;
                factoryArray[mine]->output->resources[Resource::metal] = 1;
                break;

            case factory:
                factoryArray[factory] = new Factory();
                factoryArray[factory]->input->resources[Resource::metal] = 1;
                factoryArray[factory]->output->resources[Resource::goods] = 1;
                break;
        }
    }
};
FactoryHandler::~FactoryHandler(){};

/*
The Produce function works by first checking how much resource each factory require.
It then compares this to the avalible stockpile and ranson the resources so that all factories can operate.
*/
//void FactoryHandler::produce(Resource* planetStockpile, Resource* planetResources)
void FactoryHandler::produce(Resource** planetResourcePack)
{
    Resource* planetStockpile = planetResourcePack[0];
    Resource* planetResources = planetResourcePack[1];
    Resource* request = planetResourcePack[2];

    // Clear request.
    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        request->resources[i] = 0;
    }

    // Factories requestion materials.
    for (int i = 0; i < nrOfFactories; i++)
    {
        factoryArray[i]->input->addTo(request);
    }

    // Check if all the required materials are avalible
    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        float efficiency = planetStockpile->resources[i] / request->resources[i];
        if (efficiency > 1) {efficiency = 1;}
        this->efficiency->resources[i] = efficiency;
    }

    // Produce
    for (int i = 0; i < nrOfFactories; i++)
    {
        float efficiency = 1;

        // Calculate the efficiency for the current factory depending on the avalible resources, using the lowest efficiency per factory.
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            // Check if the new efficiency is lower than the last.
            if (factoryArray[i]->input->resources[n] > 0 && this->efficiency->resources[n] < efficiency)
            {
                efficiency = this->efficiency->resources[n];
            }
        }

        printf("Efficiency[%d]: %0.4f\n", i, efficiency);

        // Calculate the production output and input depending on the efficiency.
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            this->efficiency_input->resources[n] = factoryArray[i]->input->resources[n] * efficiency;

            if (factoryArray[i]->mine)
            {
                // If factory is a mine and wants the resource from a planet
                this->efficiency_output->resources[n] = factoryArray[i]->output->resources[n] * planetResources->resources[n] * efficiency;
            } else {
                this->efficiency_output->resources[n] = factoryArray[i]->output->resources[n] * efficiency;
            }
        }

        // Sending resources to the factories
        this->efficiency_input->removeFrom(planetStockpile);
        // Returning resources from the factories
        this->efficiency_output->addTo(planetStockpile);
    }
}

Factory::Factory(){};