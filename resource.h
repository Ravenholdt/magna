#pragma once

class Resource
{
protected:

public:

    enum ResourceList
    {
        wealth,
        soil,
        ore,
        metal,
        food,
        goods,

        nrOfResources
    };

    float resources[nrOfResources] = {};

    Resource();
    ~Resource();
};