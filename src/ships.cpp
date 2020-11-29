
#include "shipParts.h"
#include "ships.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

vector<shipdesign> shipdesigns;

void designconstructor(shipdesign*);
void shipconstructor(shipdesign*, ship*);

int shipinitialization()
{
    //cout << cbrt(2) << "\n";
	shipdesigns.push_back(shipdesign());
	shipdesigns[0].name = "Deafult_design_error";
	partdeclaration();
	shipdesigns.push_back(shipdesign());
	designconstructor(&shipdesigns[1]);
	ship shippy;
	shipconstructor(&shipdesigns[1], &shippy);

	return 0;
}

void designconstructor(shipdesign* design) {

	for (int i = 0; i <= (int)PartID::partindex; i++) {
		design->partdata.push_back(partinfo());
	}
	design->partdata[0].partid = (int)PartID::command;
	design->partdata[0].partnum = 1;

	design->partdata[1].partid = (int)PartID::engine;
	design->partdata[1].partnum = 1;

	design->partdata[2].partid = (int)PartID::gun;
	design->partdata[2].partnum = 2;

	design->partdata[3].partid = (int)PartID::generator;
	design->partdata[3].partnum = 1;

	design->partdata[4].partid = (int)PartID::crewquarters;
	design->partdata[4].partnum = 4;

	design->partdata[5].partid = (int)PartID::cargospace;
	design->partdata[5].partnum = 4;
	
	for (int i = 0; i < (int)PartID::partindex; i++) {
		design->volume += (parts[design->partdata[i].partid].volume*design->partdata[i].partnum);
		design->mass += (parts[design->partdata[i].partid].mass * design->partdata[i].partnum);
		design->integrity += (parts[design->partdata[i].partid].integrity * design->partdata[i].partnum);
		design->minimumcrew += (parts[design->partdata[i].partid].crew * design->partdata[i].partnum);
		design->crewcapacity += (parts[design->partdata[i].partid].crewcapacity * design->partdata[i].partnum);
		design->power += (parts[design->partdata[i].partid].power * design->partdata[i].partnum);
		design->energystorage += (parts[design->partdata[i].partid].energystorage * design->partdata[i].partnum);
		design->cargospace += (parts[design->partdata[i].partid].cargospace * design->partdata[i].partnum);
		design->thrust += (parts[design->partdata[i].partid].thrust * design->partdata[i].partnum);

	}
	design->acceleration = ((float)design->thrust / ((float)design->mass/1000.0));
	design->profile = std::pow(std::pow(design->volume, 1 / 3.), 2.);
	design->name = "Relianze";

	/*{
		cout << "Name:	" << design->name << endl;
		cout << "Volume:	" << design->volume << endl;
		cout << "mass:	" << design->mass << endl;
		cout << "integrity:	" << design->integrity << endl;
		cout << "crew:	" << design->minimumcrew << endl;
		cout << "capacity:	" << design->crewcapacity << endl;
		cout << "power:	" << design->power << endl;
		cout << "---:	" << design->energystorage << endl;
		cout << "cargo:	" << design->cargospace << endl;
		cout << "thrust:	" << design->thrust << endl;
		cout << "acceleration:	" << design->acceleration << endl;
		cout << "profile:	" << design->profile << endl; }*/
}

void shipconstructor(shipdesign* design, ship* ship) {
	int shipCounter = galaxy.newShip();
	ship->shipid = shipCounter;
	ship->name = design->name;
	ship->name.append(" ");
	ship->name.append(to_string(ship->shipid));
	ship->cargospace = design->cargospace;
	ship->acceleration = design->acceleration;
	for (int i = 0; i < design->partdata.size(); i++) {
		ship->partdata.push_back(shippartinfo());
		ship->partdata[i].partid = design->partdata[i].partid;
		ship->partdata[i].partnum = design->partdata[i].partnum;
		int totalintegrity = 0;
		for (int j = 0; j < ship->partdata[i].partnum ; j++) {
			totalintegrity += parts[ship->partdata[i].partid].integrity;
		}
		ship->partdata[i].condition = totalintegrity;
		//cout << ship->partdata[i].condition << endl;
	}
}