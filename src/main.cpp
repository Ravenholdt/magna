#include "main.h"

using namespace std;

class Celestial
{
protected:
    int id;

    // The stockpile symbolize the resources that have been extracted and are accessible.
    Resource* stockpile = new Resource();
    // The celestial resources symbolize the materials still in the planet waiting to be extracted.
    Resource* celestialResources = new Resource();

public:
    string name;

    FactoryHandler* factories = new FactoryHandler();

    Celestial()
    {
        celestialResources->resources[Resource::metal] = 0.5;
    };
    ~Celestial(){};

    Resource* getStockpile(){ return stockpile; };
    Resource* getResources(){ return celestialResources; };
};

int main()
{
    Celestial* planet = new Celestial();

    printf("%d\n", Resource::nrOfResources);

    // Print all resources in the stockpile
    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        printf("%.1f\n", planet->getStockpile()->resources[i]);
    }

    int running = 1;
    while (running)
    {
        getchar();
        planet->factories->produce(planet->getStockpile(), planet->getResources());
        for (int i = 0; i < Resource::nrOfResources; i++)
        {
            printf("%.1f\n", planet->getStockpile()->resources[i]);
        }
    }

    return 0;
}