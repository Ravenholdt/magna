#include <iostream>

#include "system.h"

System::System(){}

System::System(int id)
{
    this->id=id;
    this->star = galaxy.newCelestial(0, 0, 2e30, 7e8, CelestialType::star);
    this->getStar()->system = this->getId();
}

Celestial* System::getStar() { return galaxy.getCelestial(this->star); }

void System::tick(long long int time)
{
    
}

void System::tickDaily()
{
    for (int i = 0; i < (int)Resources::indexLast; i++)
    {
        this->supply[i] = 0;
        this->demand[i] = 0;
    }
    this->getStar()->tickDaily();
}