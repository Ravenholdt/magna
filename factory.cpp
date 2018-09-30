#include "factory.h"

using namespace std;

FactoryHandler::FactoryHandler()
{
    for (int i = 0; i < nrOfFactories; i++)
    {
        switch(i)
        {
            case farm:
                factoryArray[farm] = new Factory();
                factoryArray[farm]->output->resources[Resource::food] = 1;
                break;

            case mine:
                //planetResources[Resource::metal] += 1;
                factoryArray[mine] = new Factory();
                factoryArray[mine]->output->resources[Resource::metal] = 1;
                break;

            case factory:
                //planetResources[Resource::metal] -= 1;
                //planetResources[Resource::goods] += 1;
                factoryArray[factory] = new Factory();
                factoryArray[factory]->input->resources[Resource::metal] = -0.5;
                factoryArray[factory]->output->resources[Resource::goods] = 1;
                break;
        }
    }
};
//FactoryHandler::~FactoryHandler(){};

//void FactoryHandler::produce(float planetResources[nrOfResources])
void FactoryHandler::produce(Resource* planetResources)
{
    //planetResources->resources[planetResources->food] += 1;
    for (int i = 0; i < nrOfFactories; i++)
    {
        // Sending resources to the factories
        factoryArray[i]->input->transferTo(planetResources);
        // Returning resources from the factories
        factoryArray[i]->output->transferTo(planetResources);
    }
}

Factory::Factory(){};