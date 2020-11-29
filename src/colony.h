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

    int structure[(int)Structures::indexLast] = {0};

    std::vector<Production> productionQueue;

    Colony();
    Colony(int id, int parent, int owner);
    ~Colony();

    void tick(long long int time);
};