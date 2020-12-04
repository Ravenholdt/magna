#pragma once

enum class Resources 
{
    metal, indexRaw, 
    infrastructure, spareParts, indexResource,
    mine, factory, indexStructure, 
    indexLast
};

//enum class Structures
//{
//    mine, factory, indexLast
//};

struct Recipe
{
    float input[(int)Resources::indexLast]={0};
    float output[(int)Resources::indexLast]={0};
};

struct Production
{
    Recipe item;
    float quantity;
};

extern Recipe recipes[];

void initiateRecipes();