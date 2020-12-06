#pragma once

enum class Resources 
{
    metal, indexRaw, 
    infrastructure, spareParts, indexResource,
    mine, factory, indexStructure, 
    indexLast
};

struct Recipe
{
    float input[(int)Resources::indexLast]={0};
    float output[(int)Resources::indexLast]={0};
};

extern Recipe recipes[];

void initiateRecipes();