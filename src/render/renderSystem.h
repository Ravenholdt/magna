#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>

void renderSolarSystem(sf::RenderWindow& window, int system);

struct renderObject
{
    sf::Vector2i pos;
    int id = -1;
    int level = 2000000000;
    int distToMouse;
};

class RenderSystem
{
private:
    sf::RenderWindow *window;

    std::vector<renderObject> renderObj;

public:
    sf::Vector2f renderOffset = sf::Vector2f(0,0);
    sf::Vector2f renderMouseOffset = sf::Vector2f(0,0);
    long long int renderTime = 0;
    float renderScaleSize = 0.001f;
    float renderScaleDistance = 5e9;
    float zoom = 1;

    sf::Vector2i mouseHoverOver;
    sf::Vector2i mouseSelected;

    void renderSolarSystem(sf::RenderWindow& window, int system);
    void drawCelestials(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level);
    void indexCelestials(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level);
    sf::Vector2i mouseToSystemPos(sf::RenderWindow& window);
    void zoomToMouse(sf::RenderWindow& window, int zoom);
    
    //void 

    //RenderSystem(/* args */);
    //~RenderSystem();
};

extern RenderSystem renderSystem;
