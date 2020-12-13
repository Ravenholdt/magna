#pragma once

enum class Resources 
{
    industrialMetals, rareMetals, preciousMetals, indexRaw, 
    infrastructure, consumerGoods, spareParts, indexResource,
    mine, factory, indexStructure, 
	//ship parts
	command, engine, gun, generator, crewquarters, cargospace, systemdrive,
    indexLast
};

struct Recipe
{
    float input[(int)Resources::indexLast]={0};
    float output[(int)Resources::indexLast]={0};
};

extern Recipe recipes[];

void initiateRecipes();