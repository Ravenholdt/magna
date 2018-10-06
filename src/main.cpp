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