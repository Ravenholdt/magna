#pragma once

#include <map>

#include "system.h"
#include "celestial.h"
#include "colony.h"

#define MINUTE  60
#define HOUR    3600
#define DAY     86400
#define WEEK    604800
#define MONTH   2628000
#define YEAR    31540000

#define KM      1000

enum class CelestialType;
class System;
class Celestial;
class Colony;

class Galaxy
{
private:
    int celestialCounter = 0;
    int systemCounter = 0;
    int colonyCounter = 0;

    long long int shipCounter = 0;
	int fleetCounter = 0;
	int shipDesignCounter = 0;
public:
    std::map<int, System> systems;
    std::map<int, Celestial> celestials;
    std::map<int, Colony> colonies;

    //Galaxy(/* args */);
    //~Galaxy();

    long long int time = 0;
    long long int hour = 0;
	long long int day = 0;
    long long int week = 0;
	long long int month = 0;
	long long int year = 0;

    int newSystem();
    int newCelestial(int parent, float distance, float mass, float radius, CelestialType type);
    int newColony(int parent);

    System*     getSystem(int id);
    Celestial*  getCelestial(int id);
    Colony*     getColony(int id);

    int newShip();
	int newFleet();
	int newShipDesign();
	float distance(int source, int target);
    
    void tick(long long int timeStep);

    void tickHourly();
    void tickDaily();
    void tickWeekly();
    void tickMonthly();
    void tickYearly();
};

extern Galaxy galaxy;