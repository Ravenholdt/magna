#include "factory.h"

using namespace std;

FactoryHandler::FactoryHandler(){};
FactoryHandler::~FactoryHandler(){};

//void FactoryHandler::produce(float planetResources[nrOfResources])
void FactoryHandler::produce(Resource* planetResources)
{
    planetResources->resources[planetResources->food] += 1;
    /*for (int i = 0; i < nrOfFactories; i++)
    {
        switch(i)
        {
            case farm:
                planetResources[Resource::food] += 1;
                break;

            case mine:
                planetResources[Resource::metal] += 1;
                break;

            case factory:
                planetResources[Resource::metal] -= 1;
                planetResources[Resource::goods] += 1;
                break;
        }
    }*/
}
