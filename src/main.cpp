#include "main.h"

using namespace std;

class Celestial
{
protected:
    int id;

    // The stockpile symbolize the resources that have been extracted and are accessible.
    Resource* stockpile = new Resource();
    // The stockpile demand is used to check the balance of avalible resources to simulate a market economy.
    Resource* stockpileDemand = new Resource();
    // The market price increase during a shortage of resources and decrease during a surplus.
    Resource* marketPrice = new Resource(1);
    // The celestial resources symbolize the materials still in the planet waiting to be extracted.
    Resource* celestialResources = new Resource();

public:
    string name;

    FactoryHandler* factories = new FactoryHandler();

    Celestial(){ celestialResources->resources[Resource::metal] = 0.5; };
    ~Celestial(){};

    Resource* getStockpile(){ return this->stockpile; };
    Resource* getResources(){ return this->celestialResources; };
    Resource* getStockpileDemand(){ return this->stockpileDemand; };
    Resource* getMarketPrice(){ return this->marketPrice; };

    //For when a function requires all resource pointers.
    Resource **getResourcePack()
    {
        static Resource* resArray[] = {this->stockpile, this->celestialResources, this->stockpileDemand, this->marketPrice};
        return resArray;
    }

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

    planet->getResourcePack();

    int running = 1;
    while (running)
    {
        getchar();
        //planet->factories->produce(planet->getStockpile(), planet->getResources());
        planet->factories->produce(planet->getResourcePack());

        // Calculate price
        for (int i = 0; i < Resource::nrOfResources; i++)
        {
            if (i != Resource::wealth)
            {
                float avalibility = planet->getStockpileDemand()->resources[i] / planet->getStockpile()->resources[i];
                if (planet->getStockpileDemand()->resources[i] == 0) { avalibility = 0.1; }
                if (planet->getStockpile()->resources[i] == 0){ avalibility = 10; }
                if (avalibility > 10){ avalibility = 10; }
                if (avalibility < 0.1) { avalibility = 0.1; }
                planet->getMarketPrice()->resources[i] *= avalibility;
            }
        }

        for (int i = 0; i < Resource::nrOfResources; i++)
        {
            printf("%.1f - %.3f\n", planet->getStockpile()->resources[i], planet->getMarketPrice()->resources[i]);
        }
    }

    return 0;
}