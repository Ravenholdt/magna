#include "factory.h"

using namespace std;

FactoryHandler::FactoryHandler(){};
FactoryHandler::~FactoryHandler(){};

void FactoryHandler::produce(float planetResources[nrOfResources])
{
    for (int i = 0; i < nrOfFactories; i++)
    {
        switch(i)
        {
            case farm:
                planetResources[food] += 1;
                break;

            case mine:
                planetResources[metal] += 1;
                break;

            case factory:
                planetResources[metal] -= 1;
                planetResources[goods] += 1;
                break;
        }
    }
}
