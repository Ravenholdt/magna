#include "shipParts.h"
part parts[(int)PartID::partindex];

void partdeclaration() {

	parts[(int)PartID::command].volume = 40; //5percrew+ 20
	parts[(int)PartID::command].mass = 10000; //1000percrew+
	parts[(int)PartID::command].integrity = 100; //20 integrity = 1000 kilos, 5 volume; 
	parts[(int)PartID::command].crew = 3;
	parts[(int)PartID::command].power = -10; //2 per crew

	parts[(int)PartID::engine].volume = 10;
	parts[(int)PartID::engine].mass = 10000;
	parts[(int)PartID::engine].integrity = 100;
	parts[(int)PartID::engine].crew = 1;
	parts[(int)PartID::engine].power = -10;
	parts[(int)PartID::engine].thrust = 100;

	parts[(int)PartID::gun].volume = 5;
	parts[(int)PartID::gun].mass = 2000;
	parts[(int)PartID::gun].integrity = 50;
	parts[(int)PartID::gun].crew = 1;
	parts[(int)PartID::gun].power = -5;

	parts[(int)PartID::generator].volume = 20;
	parts[(int)PartID::generator].mass = 5000;
	parts[(int)PartID::generator].integrity = 100;
	parts[(int)PartID::generator].crew = 1;
	parts[(int)PartID::generator].power = 50;

	parts[(int)PartID::crewquarters].volume = 10;
	parts[(int)PartID::crewquarters].mass = 2000;
	parts[(int)PartID::crewquarters].integrity = 20;
	parts[(int)PartID::crewquarters].crewcapacity = 2;
	parts[(int)PartID::crewquarters].power = -1;

	parts[(int)PartID::cargospace].volume = 15;
	parts[(int)PartID::cargospace].mass = 1000;
	parts[(int)PartID::cargospace].integrity = 10;
	parts[(int)PartID::cargospace].cargospace = 10;

	parts[(int)PartID::systemdrive].volume = 1;
	parts[(int)PartID::systemdrive].mass = 200;
	parts[(int)PartID::systemdrive].integrity = 5;
	parts[(int)PartID::systemdrive].crew = 0;
	parts[(int)PartID::systemdrive].power = -20;
	parts[(int)PartID::systemdrive].drivespeed = 150;
	parts[(int)PartID::systemdrive].drivefield = 4;
	
}


