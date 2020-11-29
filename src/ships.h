#pragma once

#include <iostream>
#include <math.h>
#include <vector>

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

struct shippartinfo {//partlists for ships
	int partid = -1, partnum = 0, condition = 0;
};
struct ship {
	string name = "Unknown";
	int shipid = 0;
	int cargo[1];
	int cargospace = 0;
	int cargomass = 0;
	float acceleration = 0;
	vector<shippartinfo> partdata;
};

extern vector<shipdesign> shipdesigns;

int shipinitialization();

