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
void FactoryHandler::produce(Resource* consumedResources, Resource* producedResources, Resource* efficiency, Resource* planetResources)
//void FactoryHandler::produce(Resource** planetResourcePack)
{
    // Produce
    for (int i = 0; i < nrOfFactories; i++)
    {
        float tmpEfficiency = 1;

        // Calculate the efficiency for the current factory depending on the avalible resources, using the lowest efficiency per factory.
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            // Check if the new efficiency is lower than the last.
            if (factoryArray[i]->input->resources[n] > 0 && efficiency->resources[n] < tmpEfficiency)
            {
                tmpEfficiency = efficiency->resources[n];
            }
        }

        printf("Efficiency[%d]: %0.4f\n", i, tmpEfficiency);

        // Calculate the production output and input depending on the efficiency.
        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            consumedResources->resources[n] += factoryArray[i]->input->resources[n] * tmpEfficiency;

            if (factoryArray[i]->mine)
            {
                // If factory is a mine and wants the resource from a planet
                producedResources->resources[n] += factoryArray[i]->output->resources[n] * planetResources->resources[n] * tmpEfficiency;
            } else {
                producedResources->resources[n] += factoryArray[i]->output->resources[n] * tmpEfficiency;
            }
        }
    }
}

// Factories requestion materials.
void FactoryHandler::request(Resource* requestedResources)
{
    for (int i = 0; i < nrOfFactories; i++)
    {
        factoryArray[i]->input->addTo(requestedResources);
    }
}

Factory::Factory(){};