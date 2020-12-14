#pragma once

#include <vector>

#include "resources.h"
#include "celestial.h"

class Celestial;

struct Population
{
    long long int amount;
    float needs[(int)Resources::indexLast] = {0};

    int lifespan = 1200;// in months
	float basegrowthmod = 0.00165; // per month
	float growthmod = 0.00165;
};


class Colony
{
    private:
    int id;

    public:
    int owner;
    int parent;

    Population population;
	float infrastructure = 0;

    float stockpileMaterials[(int)Resources::indexLast]={0};
    float production[(int)Resources::indexLast]={0};
	int factoriesNum = 0;
    float requests[(int)Resources::indexLast]={0};
	float needs[(int)Resources::indexLast]={0};

    std::vector<int> shipHangar;

    Colony();
    Colony(int id, int parent, int owner);
    ~Colony();

    void produce();

    void tick(long long int time);
    void tickDaily();
    void tickWeekly();
    void tickMonthly();
    void tickYearly();

	void popComsume();
	void popCalculator();
};