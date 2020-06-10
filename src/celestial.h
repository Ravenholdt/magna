#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "resources.h"
//#include "colony.h"

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

    float mass;
    float radius;

    std::string sprite = "GreenPlanet.png";

    sf::Color color = sf::Color::Red;
    
    long long int orbitalPeriod=1;
    int offset = 0;

    int population = 0;

    int structures[1]={0};
    float planetaryMaterials[(int)Resources::indexRaw]={0};
    int stockpileMaterials[(int)Resources::indexLast]={0};

    Celestial(int id, int parent, float distance, float mass, float radius, CelestialType type);
    Celestial();
    ~Celestial();

    //SET-GET
    int getID(){return id;}

    void addChild(int);
    int newChild(float distance, float mass, float radius, CelestialType type);
    void addToParent();

    sf::Vector2f orbitToPosSystem(long long int time);
    sf::Vector2f orbitToPosParent(long long int time);
    void tick();
    void print();
};