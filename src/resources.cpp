
#include <iostream>

#include "resources.h"

Recipe recipes[(int)Resources::indexLast];

void initiateRecipes()
{
    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        switch (i)
        {
        case (int)Resources::infrastructure:
            recipes[i].input[(int)Resources::metal] = 1;
            recipes[i].output[(int)Resources::infrastructure] = 1;
            break;
        
        case (int)Resources::mine:
            recipes[i].input[(int)Resources::metal] = 1;
            recipes[i].output[(int)Resources::mine] = 1;
            break;

        case (int)Resources::factory:
            recipes[i].input[(int)Resources::metal] = 1;
            recipes[i].output[(int)Resources::mine] = 1;
            break;
        
        default:
            std::cout << i << " - Not implemented." << std::endl;
            break;
        }
    }
}