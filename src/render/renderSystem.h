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
    float renderScale = 5e9;
    float zoom = 1;

    struct Mouse
    {
        bool mouseHold = 0;
        sf::Vector2i mouseHoldStartPosition;
    }mouse;

    struct Selected
    {
        sf::Vector2i hover; // x = RenderObject, y = celestial
        sf::Vector2i selected; // x = RenderObject, y = celestial
        sf::Vector2f mouseSelectedStartPosition;
        sf::Vector2f mouseSelectedLastOffset;
    }selected;

    struct ScreenToPoint
    {
        enum Lock { jumpTo, unlocked, permanent };

        int locked = unlocked;
        sf::Vector2f screen;
        sf::Vector2f game;
    }screenToPoint;

    sf::Vector2i mouseToSystemPos(sf::RenderWindow& window);
    sf::Vector2f systemPosToScreen(sf::Vector2f pos);

    void renderSolarSystem(sf::RenderWindow& window, int system);
    void drawCelestials(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level);
    sf::Vector2f getCelestialScreenPos(int celestial);
    void indexCelestials(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level);

    void LockScreenToPoint(int lock, sf::Vector2f screen, sf::Vector2f game);
    void zoomToMouse(sf::RenderWindow& window, int zoom);
    void zoomToCelestial(int zoom);
    
    //void 

    //RenderSystem(/* args */);
    //~RenderSystem();
};

extern RenderSystem renderSystem;
