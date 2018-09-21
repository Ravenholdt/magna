#include "main.h"

using namespace std;

class Celestial
{
protected:
    int id;

    float population;
    float resources[nrOfResources];

public:
    string name;

    Celestial(){};
    ~Celestial(){};

    float* getResources(){
        return resources;
    };
};

int main()
{
    printf("%d\n", nrOfResources);

    Celestial* earth = new Celestial();
    FactoryHandler* factories = new FactoryHandler();


    int running = 1;
    while (running)
    {
        getchar();
        factories->produce(earth->getResources());
        for (int i = 0; i < nrOfResources; i++)
        {
            printf("%.0f\n", earth->getResources()[i]);
        }
    }

    return 0;
}