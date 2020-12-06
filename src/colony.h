#pragma once

#include <vector>

#include "resources.h"
#include "celestial.h"

class Celestial;

class Colony
{
    private:
    int id;

    public:
    int owner;
    int parent;

    long long int population;

    float stockpileMaterials[(int)Resources::indexLast]={0};
    float production[(int)Resources::indexLast]={0};
    float requests[(int)Resources::indexLast]={0};

    long long int lastProduce;

    std::vector<int> shipHangar;

    Colony();
    Colony(int id, int parent, int owner);
    ~Colony();

    void produce();

    void tick(long long int time);
};