#include "resource.h"

#include <iostream>

Resource::Resource()
{
    /*for (int i = 0; i < nrOfResources; i++)
        resources[i] = 0;*/
}

void Resource::transferTo(Resource* target)
{
    for (int i = 0; i < nrOfResources; i++)
    {
        target->resources[i] += this->resources[i];
    }
}