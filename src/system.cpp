#include <iostream>

#include "galaxy.h"

System::System(){}

System::System(int id)
{
    this->id=id;
    this->star = galaxy.newCelestial(0, 0, 2e30, 7e8);
    galaxy.celestials[this->star].isStar = true;
}