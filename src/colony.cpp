
#include <iostream>

#include "galaxy.h"
#include "colony.h"


Colony::Colony(int id, int parent, int owner)
{
    this->id = id;
    this->parent = parent;
    this->owner = owner;

    this->structure[(int)Structures::mine] = 1;
    this->structure[(int)Structures::factory] = 1;

    Production production;
    production.item = recipes[(int)Resources::infrastructure];
    production.quantity = 100;

    this->productionQueue.push_back(production);
}

Colony::Colony(){}
Colony::~Colony(){}

void Colony::tick(long long int time)
{
    std::cout << "Colony: " << this->id << std::endl;

    for(int s = (int)Structures::mine; s < (int)Structures::indexLast; s++)
    {
        switch (s)
        {
        case (int)Structures::mine:
            for (int i = 0; i < (int)Resources::indexRaw; i++)
            {
                galaxy.celestials[this->parent].stockpileMaterials[i] += 
                    galaxy.celestials[this->parent].planetaryMaterials[i] * this->structure[(int)Structures::mine];
            }
            std::cout << std::endl;
            break;

        case (int)Structures::factory:
        {
            float productionCapacity = this->structure[(int)Structures::factory];
            int productionStep = 0;
            while (productionStep < productionQueue.size() && productionCapacity > 0)
            {
                float quota = this->productionQueue[productionStep].quantity;
                float ratio = 1;

                std::cout << quota << " : " << ratio << std::endl;
                std::cout << this->productionQueue[productionStep].item.input[(int)Resources::metal] << std::endl;

                if (productionCapacity < quota)
                { 
                    quota = productionCapacity; 
                }

                for (int i = 0; i < (int)Resources::indexLast; i++)
                {
                    // Check if resources are avalible
                    if (this->productionQueue[productionStep].item.input[i] > 0)
                    {
                        float newRatio = galaxy.celestials[this->parent].stockpileMaterials[i] / this->productionQueue[productionStep].item.input[i] * quota;
                        if (newRatio < 0) { newRatio = 0; }
                        if (newRatio < ratio)
                        {
                            ratio = newRatio;
                        }
                    }
                }

                std::cout << quota << " : " << ratio << std::endl;

                quota *= ratio;

                std::cout << quota << " : " << ratio << std::endl;
                
                // Consume and build
                for (int i = 0; i < (int)Resources::indexLast; i++)
                {
                    // Check if resources are avalible
                    galaxy.celestials[this->parent].stockpileMaterials[i] -= (float)this->productionQueue[productionStep].item.input[i] * quota;
                    galaxy.celestials[this->parent].stockpileMaterials[i] += (float)this->productionQueue[productionStep].item.output[i] * quota;
                }

                std::cout << quota << " : " << ratio << std::endl;

                productionCapacity -= quota;
                productionStep++;
            }
            break;
        }
        
        default:
            break;
        }
    }

    for (int i = 0; i < (int)Resources::indexRaw; i++)
    {
        std::cout << galaxy.celestials[this->parent].planetaryMaterials[i] << ", ";
    }
    std::cout << std::endl;

    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        std::cout << galaxy.celestials[this->parent].stockpileMaterials[i] << ", ";
    }
    std::cout << std::endl;
}