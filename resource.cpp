#include "resource.h"

#include <iostream>

Resource::Resource()
{
    /*for (int i = 0; i < nrOfResources; i++)
        resources[i] = 0;*/
}

void Resource::transferTo(Resource* target, Resource* amount)
{
    for (int i = 0; i < nrOfResources; i++)
    {
        target->resources[i] += amount->resources[i];
        this->resources[i] -= amount->resources[i];
    }
}

void Resource::addTo(Resource* target)
{
    for (int i = 0; i < nrOfResources; i++)
    {
        target->resources[i] += this->resources[i];
    }
}

void Resource::removeFrom(Resource* target)
{
    for (int i = 0; i < nrOfResources; i++)
    {
        target->resources[i] -= this->resources[i];
    }
}