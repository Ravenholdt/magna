#include "main.h"

using namespace std;

class Celestial
{
protected:
    int id;

    Resource* stockpile = new Resource();
    Resource* celestialResources = new Resource();

public:
    string name;

    Celestial()
    {
        celestialResources->resources[Resource::metal] = 0.5;
    };
    ~Celestial(){};

    Resource* getStockpile(){
        return stockpile;
    };

    Resource* getResources(){
        return celestialResources;
    };
};

int main()
{
    Celestial* planet = new Celestial();
    FactoryHandler* factories = new FactoryHandler();

    printf("%d\n", Resource::nrOfResources);

    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        printf("%.1f\n", planet->getStockpile()->resources[i]);
    }

    int running = 1;
    while (running)
    {
        getchar();
        factories->produce(planet->getStockpile(), planet->getResources());
        for (int i = 0; i < Resource::nrOfResources; i++)
        {
            printf("%.1f\n", planet->getStockpile()->resources[i]);
        }
    }

    return 0;
}