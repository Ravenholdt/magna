#pragma once

//#include <SFML/Graphics.hpp>

#include <vector>

#include "resources.h"
#include "colony.h"

enum class CelestialType {star, planet, dwarfPlanet, moon, asteroid};

class Celestial
{
    private:
    int id;

    public:
    CelestialType type = CelestialType::planet;
    int parent;
    float distance;
    
    std::vector<int> childs;
    std::vector<int> colonies;

    float mass;
    float radius;
    
    long long int orbitalPeriod=1;
    int offset = 0;

    int population = 0;

    float planetaryMaterials[(int)Resources::indexRaw]={0};

    float stockpileMaterials[(int)Resources::indexLast]={0};
    float consumption [(int)Resources::indexLast]={0};
    float price[(int)Resources::indexLast]={0};

    Celestial(int id, int parent, float distance, float mass, float radius, CelestialType type);
    Celestial();
    ~Celestial();

    //SET-GET
    int getID(){return id;}

    void addChild(int);
    int newChild(float distance, float mass, float radius, CelestialType type);
    int newColony(int parent);
    void addToParent();

    void tick(long long int time);
    void print();
};