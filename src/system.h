#pragma once

#include <string>

class System
{
private:
    int id;
public:
    int star;
    
    System();
    System(int id);
    //~System();

    void addCelestial(int parent, float mass, float distance);
};
