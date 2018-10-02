#include "main.h"

using namespace std;

class Celestial
{
protected:
    int id;

    //float resources[Resource::nrOfResources];
    Resource* stockpile = new Resource();

public:
    string name;

    Celestial(){};
    ~Celestial(){};

    Resource* getStockpile(){
        return stockpile;
    };
};

int main()
{
    Celestial* earth = new Celestial();
    FactoryHandler* factories = new FactoryHandler();

    printf("%d\n", Resource::nrOfResources);
    //printf("%.0f!\n", Farm.output[food]);

    for (int i = 0; i < Resource::nrOfResources; i++)
    {
        printf("%.1f\n", earth->getStockpile()->resources[i]);
    }

    int running = 1;
    while (running)
    {
        getchar();
        factories->produce(earth->getStockpile());
        for (int i = 0; i < Resource::nrOfResources; i++)
        {
            printf("%.1f\n", earth->getStockpile()->resources[i]);
        }
    }

    return 0;
}