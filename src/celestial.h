#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "resources.h"
//#include "colony.h"

class Celestial
{
    private:
    int id;

    public:
    bool isStar = false;
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

    Celestial(int id, int parent, float distance, float mass, float radius);
    Celestial();
    ~Celestial();

    //SET-GET
    int getID(){return id;}

    void addChild(int);
    int newChild(float distance, float mass, float radius);
    void addToParent();

    sf::Vector2f orbitToPos(long long int time);
    void tick();
    void print();
};