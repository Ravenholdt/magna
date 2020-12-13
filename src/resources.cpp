
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
            recipes[i].input[(int)Resources::industrialMetals] = 1;
            recipes[i].output[(int)Resources::infrastructure] = 1;
            break;
        
        case (int)Resources::mine:
            recipes[i].input[(int)Resources::industrialMetals] = 1;
            recipes[i].output[(int)Resources::mine] = 1;
            break;

        case (int)Resources::factory:
            recipes[i].input[(int)Resources::industrialMetals] = 1;
            recipes[i].output[(int)Resources::factory] = 1;
            break;
			//consumer goods
		case (int)Resources::consumerGoods:
			recipes[i].input[(int)Resources::industrialMetals] = 1;
			recipes[i].output[(int)Resources::consumerGoods] = 1;

			//ship parts
		case (int)Resources::command:
			recipes[i].input[(int)Resources::industrialMetals] = 1;
			recipes[i].output[(int)Resources::command] = 0.1;
			break;
		case (int)Resources::engine:
			recipes[i].input[(int)Resources::industrialMetals] = 1;
			recipes[i].output[(int)Resources::engine] = 0.1;
			break;
		case (int)Resources::gun:
			recipes[i].input[(int)Resources::industrialMetals] = 1;
			recipes[i].output[(int)Resources::gun] = 0.5;
			break;
		case (int)Resources::generator:
			recipes[i].input[(int)Resources::industrialMetals] = 1;
			recipes[i].output[(int)Resources::generator] = 0.2;
			break;
		case (int)Resources::crewquarters:
			recipes[i].input[(int)Resources::industrialMetals] = 1;
			recipes[i].output[(int)Resources::crewquarters] = 0.5;
			break;
		case (int)Resources::cargospace:
			recipes[i].input[(int)Resources::industrialMetals] = 1;
			recipes[i].output[(int)Resources::cargospace] = 1;
			break;
		case (int)Resources::systemdrive:
			recipes[i].input[(int)Resources::industrialMetals] = 0.2;
			recipes[i].output[(int)Resources::systemdrive] = 0.2;
			break;
        default:
            std::cout << i << " - Not implemented." << std::endl;
            break;
        }
    }
}