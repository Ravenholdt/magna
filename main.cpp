#include "main.h"

using namespace std;

class Celestial
{
protected:
    int id;

    //float resources[Resource::nrOfResources];
    Resource* resources = new Resource();

public:
    string name;

    Celestial(){};
    ~Celestial(){};

    Resource* getResources(){
        return resources;
    };
};

int main()
{
    Celestial* earth = new Celestial();
    FactoryHandler* factories = new FactoryHandler();

    printf("%d\n", earth->getResources()->nrOfResources);
    //printf("%.0f!\n", Farm.output[food]);

    for (int i = 0; i < earth->getResources()->nrOfResources; i++)
    {
        printf("%.1f\n", earth->getResources()->resources[i]);
    }

    int running = 1;
    while (running)
    {
        getchar();
        factories->produce(earth->getResources());
        for (int i = 0; i < earth->getResources()->nrOfResources; i++)
        {
            printf("%.1f\n", earth->getResources()->resources[i]);
        }
    }

    return 0;
}