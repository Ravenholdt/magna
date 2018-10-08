#include "main.h"

using namespace std;

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
        //planet->factories->produce(planet->getStockpile(), planet->getResources());
        //planet->factories->produce(planet->getResourcePack());
        planet->tick();

        for (int i = 0; i < Resource::nrOfResources; i++)
        {
            printf("%.1f - %.3f\n", planet->getStockpile()->resources[i], planet->getMarketPrice()->resources[i]);
        }
    }

    return 0;
}