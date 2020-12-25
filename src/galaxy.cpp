
#include <iostream>
#include <iterator>

#include "galaxy.h"
#include "ships.h"

Galaxy galaxy;

System*     Galaxy::getSystem(int id)       { return &galaxy.systems[id]; }
Celestial*  Galaxy::getCelestial(int id)    { return &galaxy.celestials[id]; }
Colony*     Galaxy::getColony(int id)       { return &galaxy.colonies[id]; }

int Galaxy::newCelestial(int parent, float distance, float mass, float radius, CelestialType type)
{
    celestialCounter++;
    this->celestials[celestialCounter] = Celestial(celestialCounter, parent, distance, mass, radius, type);
    this->celestials[celestialCounter].addToParent();
    return celestialCounter;
}

int Galaxy::newSystem()
{
    systemCounter++;
    this->systems[systemCounter] = System(systemCounter);
    return systemCounter;
}

int Galaxy::newColony(int parent)
{
    colonyCounter++;
    this->colonies[colonyCounter] = Colony(colonyCounter, parent, 0);
    return colonyCounter;
}

int Galaxy::newShip()
{
    shipCounter++;
    return shipCounter;
}

int Galaxy::newFleet() 
{
	fleetCounter++;
	return fleetCounter;
}

int Galaxy::newShipDesign() {
	shipDesignCounter++;
	return shipDesignCounter;
}

float Galaxy::distance(int source, int target)
{
    float sx, sy, tx, ty;
    float dx, dy;

    galaxy.celestials[source].getPosInSystem(&sx, &sy, galaxy.time);
    galaxy.celestials[target].getPosInSystem(&tx, &ty, galaxy.time);

    dx = abs(sx - tx);
    dy = abs(sy - ty);

    return sqrt(pow(dx, 2)+pow(dy, 2));
}

void Galaxy::tick(long long int timeStep)
{
    //this->time += timeStep;
	long long int end = timeStep + this->time;
    std::cout << "Time: " << time << std::endl;
	
	while (this->time < end) {
        if (this->hour < (int)(this->time / HOUR)) //day
		{
			this->hour++;
			
            this->tickHourly();
		}

		if (this->day < (int)(this->time / DAY)) //day
		{
			this->day++;
			cout << "New day:	" << this->day << endl;
			
            this->tickDaily();
		}

        if (this->week < (int)(this->time / WEEK))// moth
		{
			this->week++;
			cout << "New week:	" << this->week << endl;

            this->tickWeekly();
		}

		if (this->month < (int)(this->time / MONTH))// moth
		{
			this->month++;
			cout << "New month:	" << this->month << endl;

            this->tickMonthly();
		}

		if (this->year < (int)(this->time / YEAR)) {// year
			this->year++;
			cout << "New year:	" << this->year << endl;

            this->tickYearly();
		}
		this->time += HOUR;
	}
	
}

void Galaxy::tickHourly()
{
    arrivalcheck();
}

void Galaxy::tickDaily()
{
    for (std::pair<int, System> element : this->systems) {
        element.second.tickDaily();
    }
}

void Galaxy::tickWeekly()
{
    //for (std::pair<int, Celestial> element : this->celestials) {
    //    element.second.tickWeekly();
    //}
}

void Galaxy::tickMonthly()
{
    for (std::pair<int, Celestial> element : this->celestials) {
        element.second.tickMonthly();
    }
}
void Galaxy::tickYearly()
{
    //for (std::pair<int, Celestial> element : this->celestials) {
    //    element.second.tickYearly();
    //}
}