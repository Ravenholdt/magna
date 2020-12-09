#pragma once

//#include <SFML/Graphics.hpp>

#include <vector>

#include "resources.h"
#include "colony.h"
#include "galaxy.h"

enum class CelestialType {star, planet, dwarfPlanet, moon, asteroid};

class Celestial
{
    private:
    int id;

    public:
    CelestialType type = CelestialType::planet;
    int parent;
    float distance;

    float atmosphere = 0;
    float habitability;
    
    std::vector<int> childs;
    std::vector<int> colonies;

    float mass;
    float radius;
    
    long long int orbitalPeriod=1;
    int offset = 0;

    float planetaryMaterials[(int)Resources::indexRaw]={0};

    float stockpileMaterials[(int)Resources::indexLast]={0};
    float demand [(int)Resources::indexLast]={0};
    float priceBase[(int)Resources::indexLast]={0};
    float priceMod[(int)Resources::indexLast]={0};

    Celestial(int id, int parent, float distance, float mass, float radius, CelestialType type);
    Celestial();
    ~Celestial();

    //SET-GET
    int getID(){return id;}
    float gravity();
    float deltaV();

    void addChild(int);
    int newChild(float distance, float mass, float radius, CelestialType type);
    int newColony(int parent);
    void addToParent();

    void getPosInSystem(float* x, float* y, long long int time);

    void tick(long long int time);
    void tickDaily();
    void tickWeekly();
    void tickMonthly();
    void tickYearly();

    void print();
};