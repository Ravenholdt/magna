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

    // Transfer amount from this to target
    void transferTo(Resource* target, Resource* amount);

    // Add this amount to target
    void addTo(Resource* target);

    // Remove this amount from target
    void removeFrom(Resource* target);
};