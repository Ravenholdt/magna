
#include <iostream>

#include "galaxy.h"
#include "colony.h"

using namespace std;


Colony::Colony(int id, int parent, int owner)
{
    this->id = id;
    this->parent = parent;
    this->owner = owner;

    this->stockpileMaterials[(int)Resources::mine] = 1;
    this->production[(int)Resources::infrastructure] = 1;
}

Colony::Colony(){}
Colony::~Colony(){}

void Colony::produce()
{
    float request[(int)Resources::indexLast] = {0};
    float ratio[(int)Resources::indexLast] = {0};

    // Go through all factories and list their consumptions.
    for (int prod = 0; prod < (int)Resources::indexLast; prod++)
    {
        for (int i = 0; i < (int)Resources::indexLast; i++)
        {
            request[i] += recipes[prod].input[i]*production[prod];
        }
    }

    // Check avalability of resources
    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        ratio[i] = 1;
        float newRatio = 1;
        if (request[i]) newRatio = this->stockpileMaterials[i] / request[i];
        if (newRatio < ratio[i]) ratio[i] = newRatio;
    }

    // Go through all factories and produce and consume.
    for (int prod = 0; prod < (int)Resources::indexLast; prod++)
    {
        float efficency = 1;
        for (int i = 0; i < (int)Resources::indexLast; i++)
        {
            float newefficency = ratio[i];
            if (newefficency < efficency) efficency = newefficency;
        }

        for (int i = 0; i < (int)Resources::indexLast; i++)
        {
            this->stockpileMaterials[i] -= recipes[prod].input[i]*production[prod]*efficency;
            this->stockpileMaterials[i] += recipes[prod].output[i]*production[prod]*efficency;
        }
    }
}

void Colony::tick(long long int time)
{
    std::cout << "Colony: " << this->id << std::endl;
    
    // Mine
    for (int i = 0; i < (int)Resources::indexRaw; i++)
    {
        this->stockpileMaterials[i] += galaxy.celestials[this->parent].planetaryMaterials[i] * this->stockpileMaterials[(int)Resources::mine];
    }

    this->produce();

    for (int i = 0; i < (int)Resources::indexRaw; i++)
    {
        std::cout << galaxy.celestials[this->parent].planetaryMaterials[i] << ", ";
    }
    std::cout << std::endl;

    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        std::cout << this->stockpileMaterials[i] << ", ";
    }
    std::cout << std::endl;

    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        std::cout << this->production[i] << ", ";
    }
    std::cout << std::endl;

	this->popCalculator();

}

void Colony::popCalculator() {
	long long int pop = this->population;
	long long int deaths = pop / this->lifespan;
	long long int growth = pop * this->growthmod;
	this->population -= deaths;
	this->population += growth;
	/*std::cout << endl;
	std::cout << "Pop:	" << pop << endl;
	std::cout << "deaths:	" << deaths << endl;
	std::cout << "growth:	" << growth << endl;
	
	std::cout << endl;*/
	std::cout << "newpop:	" << this->population << endl;;
}