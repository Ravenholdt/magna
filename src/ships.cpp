
#include "shipParts.h"
#include "ships.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <list>
#include <map>

vector<shipdesign> shipdesigns;
map<int, ship> shipmap;
map<int,fleet> fleets;
list<int> travelitterary;

int shipinitialization()
{
    //cout << cbrt(2) << "\n";
	shipdesigns.push_back(shipdesign());
	shipdesigns[0].name = "Deafult_design_error";
	partdeclaration();
	shipdesigns.push_back(shipdesign());
	designconstructor(&shipdesigns[1]);

	for (int i = 0; i < 3; i++)
		shipconstructor(&shipdesigns[1]);

	fleetconstructor(&shipmap.begin()->second, galaxy.celestials[3]);

	//for (map<int, ship>::iterator it = shipmap.begin(); it != shipmap.end(); ++it)
	//	cout << it->second.name << '\n';

	//cout << fleetlist.front().name << endl;

	//addtofleet(&shippy, &fleety);

	//movefleet(4,5,fleetlist.front());
	
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

void shipconstructor(shipdesign* design) {
	int shipCounter = galaxy.newShip();
	shipmap[shipCounter].shipid = shipCounter;
	shipmap[shipCounter].name = design->name;
	shipmap[shipCounter].name.append(" ");
	shipmap[shipCounter].name.append(to_string(shipmap[shipCounter].shipid));
	shipmap[shipCounter].cargospace = design->cargospace;
	shipmap[shipCounter].acceleration = design->acceleration;
	for (int i = 0; i < design->partdata.size(); i++) {
		shipmap[shipCounter].partdata.push_back(shippartinfo());
		shipmap[shipCounter].partdata[i].partid = design->partdata[i].partid;
		shipmap[shipCounter].partdata[i].partnum = design->partdata[i].partnum;
		int totalintegrity = 0;
		for (int j = 0; j < shipmap[shipCounter].partdata[i].partnum ; j++) {
			totalintegrity += parts[shipmap[shipCounter].partdata[i].partid].integrity;
		}
		shipmap[shipCounter].partdata[i].condition = totalintegrity;
	}
}

void fleetconstructor(ship* ship, Celestial orbit) {
	int fleetid = galaxy.newFleet();
	fleets[fleetid].fleetid = fleetid;
	fleets[fleetid].name = "Numero uno fleet";
	fleets[fleetid].location = orbit.getID();
	//fleets[fleetid].ships

	fleetid++;
}

void addtofleet() {
	
}

void removefromfleet() {

}

void deletefleet() {

}

void movefleet(int source, int target, fleet* fleet) {
	long int distance = galaxy.Distance(source, target);
	int i = 1, starFinder = source;
	/*
	cout << "transit data: ";
	cout << (int)galaxy.celestials[galaxy.celestials[starFinder].parent].type << "	";	//0 star, 1 planet, 2 dwarfPlanet, 3 moon, 4 asteroid
	cout << (int)galaxy.celestials[galaxy.celestials[starFinder].parent].getID() << "	";
	*/
	while (i > 0) {// departure, ska det verkligen vara så här mycket kod för att hitta stjärnan i systemet?
		if ((int)galaxy.celestials[galaxy.celestials[starFinder].parent].type == (int)CelestialType::star) {
			fleet->location = (int)galaxy.celestials[galaxy.celestials[starFinder].parent].getID();
			i = 0;
		}
		else {
			starFinder = (int)galaxy.celestials[galaxy.celestials[starFinder].parent].getID();
			i++;
			if (i > 100) i = 0;
		}
	}
	//cout << fleet->location << endl;
	
	fleet->arrivaltime = galaxy.time; + (distance/fleet->travelspeed);
	//travelitterary.push_back(fleet);//lägger flottan i en lista som ittereras över lite då och då för att koll om något kommit fram.
	
	
}

void arrivalcheck(){// TODO		//göra om alla lists till maps?
	//something something traveliterary
}