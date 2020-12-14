
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

    this->population.needs[(int)Resources::consumerGoods] = 0.0005;
}

Colony::Colony(){}
Colony::~Colony(){}

void Colony::produce()
{
    float request[(int)Resources::indexLast] = {0};
    float ratio[(int)Resources::indexLast] = {0};
    float workforceRatio;

    // Go through all factories and check avalible workforce.
    float requiredWorkforce = 0;
    for (int prod = 0; prod < (int)Resources::indexLast; prod++)
    {
        requiredWorkforce += recipes[prod].workforce;
    }

    if (requiredWorkforce)
    {
        workforceRatio = this->population.amount / requiredWorkforce;
        if (workforceRatio > 1) { workforceRatio = 1; }
    }

    // Go through all factories and list their consumptions.
    for (int prod = 0; prod < (int)Resources::indexLast; prod++)
    {
        for (int i = 0; i < (int)Resources::indexLast; i++)
        {
            request[i] += recipes[prod].input[i] * production[prod] * workforceRatio;
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
            this->stockpileMaterials[i] -= recipes[prod].input[i] * production[prod] * efficency;
            this->stockpileMaterials[i] += recipes[prod].output[i] * production[prod] * efficency;
        }
    }
}

void Colony::tick(long long int time){}

void Colony::tickDaily()
{
    std::cout << "Colony: " << this->id << std::endl;
    
    // Mine
    for (int i = 0; i < (int)Resources::indexRaw; i++)
    {
        this->stockpileMaterials[i] += galaxy.celestials[this->parent].planetaryMaterials[i] * this->stockpileMaterials[(int)Resources::mine];
    }
	//cout <<"avalibility:	" << galaxy.celestials[this->parent].planetaryMaterials[(int)Resources::industrialMetals] << endl;

    this->produce();
	/*
    for (int i = 0; i < (int)Resources::indexRaw;	i++)
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
	*/
	Colony::popComsume();
	cout << "Metals:	" << (long long int)this->stockpileMaterials[(int)Resources::industrialMetals] << endl;
	cout << "Goods:	" << (long long int)this->stockpileMaterials[(int)Resources::consumerGoods] << endl;
	
}

void Colony::popComsume() {
	float consumergoodsAvalibility = this->stockpileMaterials[(int)Resources::consumerGoods] / (this->population.amount * this->population.needs[(int)Resources::consumerGoods]);
	cout << this->stockpileMaterials[(int)Resources::consumerGoods] << endl;
	cout << "Avalibility:	" << consumergoodsAvalibility << endl;
	if (consumergoodsAvalibility < 1) {
		this->stockpileMaterials[(int)Resources::consumerGoods] = 0;
	}
	else {
        // consume 1 per 100 per month in daily ticks.
		this->stockpileMaterials[(int)Resources::consumerGoods] -= (this->population.amount * this->population.needs[(int)Resources::consumerGoods]);
	}
}

void Colony::popCalculator() {
	long long int pop = this->population.amount;
	long long int deaths = pop / this->population.lifespan;
	long long int growth = pop * this->population.growthmod;
	this->population.amount -= deaths;
	this->population.amount += growth;
	std::cout << "newpop:	" << this->population.amount << endl;
}

void Colony::tickMonthly()
{
    //this->popCalculator();
}