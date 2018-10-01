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
                factoryArray[factory]->input->resources[Resource::metal] = 1;
                factoryArray[factory]->output->resources[Resource::goods] = 1;
                break;
        }
    }
};
FactoryHandler::~FactoryHandler(){};

//void FactoryHandler::produce(float planetResources[nrOfResources])
void FactoryHandler::produce(Resource* planetResources)
{
    Resource* request = new Resource();

    // Factories requestion materials.
    for (int i = 0; i < nrOfFactories; i++)
    {
        factoryArray[i]->input->addTo(request);
    }

    // Check if all the required materials are avalible
    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        float efficiency = planetResources->resources[i] / request->resources[i];
        if (efficiency > 1) {efficiency = 1;}
        this->efficiency->resources[i] = efficiency;
    }

    for (int i = 0; i < nrOfFactories; i++)
    {
        float efficiency = 1;

        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            if (factoryArray[i]->input->resources[n] > 0 && this->efficiency->resources[n] < efficiency)
            {
                efficiency = this->efficiency->resources[n];
            }
        }

        printf("Efficiency[%d]: %0.4f\n", i, efficiency);

        for (int n = 0; n < Resource::nrOfResources; n++)
        {
            this->efficiency_input->resources[n] = factoryArray[i]->input->resources[n] * efficiency;
            this->efficiency_output->resources[n] = factoryArray[i]->output->resources[n] * efficiency;
        }

        // Sending resources to the factories
        this->efficiency_input->removeFrom(planetResources);
        // Returning resources from the factories
        this->efficiency_output->addTo(planetResources);
    }
}

Factory::Factory(){};