#pragma once
#include <iostream>
#include <math.h>

using namespace std;

enum class PartID { command, engine, gun, generator, crewquarters, cargospace, systemdrive, partindex };

struct part {
	string name = "ERROR";
	int volume = 0,/*m3*/ mass = 0/*kilos*/, integrity = 0, crew = 0, crewcapacity = 0, power = 0, energystorage = 0, armor = 0, cargospace = 0, thrust = 0, drivespeed = 0, drivefield = 0;
};

extern part parts[];

void partdeclaration();
