#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include <list>
#include <map>

#include "resources.h"
#include "galaxy.h"

using namespace std;

struct partinfo {//partlists for shipdesigns, so it lacks current condition,
	int partid = -1, partnum = 0;
};
struct shipdesign {
	string name = "Deafult_design_error";
	long int volume = 0, mass = 0, integrity = 0;
	int minimumcrew = 0, crewcapacity = 0, power = 0, energystorage = 0, cargospace, thrust = 0;
	
	float acceleration = 0, profile = -1;
	vector<partinfo> partdata;
};

extern vector<shipdesign> shipdesigns;

struct shippartinfo {//partlists for ships
	int partid = -1, partnum = 0, condition = 0;
};
struct ship {
	string name = "Unknown";
	int shipid = 0;
	int cargospace = 0;
	int cargomass = 0;
	float acceleration = 0;
	vector<shippartinfo> partdata;
};

extern map<int, ship> shipmap;

struct fleet {
	string name;
	int fleetid;
	long int cargospace;
	int resources[(int)Resources::indexLast];
	std::list<int> ships;
	int location = 0;
	int travelspeed = 1;
	long long int arrivaltime;
	int target = 0;
};

extern std::map<int,fleet> fleets;
extern std::map<int, int> travelitterary;//list of all fleets in transit

int shipinitialization();
void designconstructor(shipdesign*);
void shipconstructor(shipdesign*);

void fleetconstructor(ship*, Celestial);
void addtofleet();
void removefromfleet();
void deletefleet();
void movefleet(int, int, int);
void arrivalcheck();

