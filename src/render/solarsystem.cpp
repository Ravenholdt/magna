#include <iostream>
#include <string>
#include <math.h>

#include "solarsystem.h"
#include "../galaxy.h"
#include "textures.h"

bool old = false;

sf::Vector2f renderOffset(0,0);
long long int renderTime = 0;
float renderScaleSize = 0.001f;
float renderScaleDistance = 5e9;
float zoom = 1;


void drawCelestialsOld(sf::RenderWindow& window, int celestial, sf::Vector2u pos, int level)
{
    if (galaxy.celestials[celestial].parent)
    {
        sf::Sprite sprite = textures.sprites[galaxy.celestials[celestial].sprite];
        sprite.setPosition(pos.x, pos.y);
        sprite.setScale(sf::Vector2f(0.1f, 0.1f));

        window.draw(sprite);
    }

    if (!galaxy.celestials[celestial].childs.size()) return;

    int numChilds = galaxy.celestials[celestial].childs.size();

    for(int child = 0 ; child < galaxy.celestials[celestial].childs.size() ; child++) 
    {
        if (level) pos.y += 100;
        else pos.x += 120;
        drawCelestialsOld(window, galaxy.celestials[galaxy.celestials[celestial].childs[child]].getID(), sf::Vector2u(pos.x, pos.y), level+1);
    }
}

void drawCelestials(sf::RenderWindow& window, int celestial, sf::Vector2u pos, int level)
{
    if (old) drawCelestialsOld(window, celestial, pos, level);
    else
    {
        int dotSize = 3;
        sf::CircleShape beacon(dotSize);
        beacon.setOrigin(sf::Vector2f(dotSize,dotSize));

        sf::Sprite sprite = textures.sprites[galaxy.celestials[celestial].sprite];
        sf::Vector2f celPos(galaxy.celestials[celestial].orbitToPos(renderTime));
        if (level)
            sprite.setPosition(pos.x + (celPos.x / renderScaleDistance * std::pow(10, zoom/10)), 
                               pos.y + (celPos.y / renderScaleDistance * std::pow(10, zoom/10)));
        else
            sprite.setPosition(pos.x + celPos.x * renderScaleDistance, pos.y + celPos.y * renderScaleDistance);
        float scale = log(galaxy.celestials[celestial].radius/2) * renderScaleSize;
        sprite.setScale(sf::Vector2f(scale, scale));

        beacon.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
        window.draw(beacon);
        //window.draw(sprite);

        double test = celPos.x / renderScaleDistance;
        std::cout << renderScaleDistance << std::endl;
        std::cout << celPos.x << " : " << sprite.getPosition().x << " : " << celPos.x - sprite.getPosition().x << " : " << test << std::endl;
        //std::cout << "Scale: " << renderScaleDistance << std::endl;
        
        if (!galaxy.celestials[celestial].childs.size()) return;

        int numChilds = galaxy.celestials[celestial].childs.size();

        for(int child = 0 ; child < galaxy.celestials[celestial].childs.size() ; child++) 
        {
            drawCelestials(window, galaxy.celestials[galaxy.celestials[celestial].childs[child]].getID(), 
                sf::Vector2u(sprite.getPosition().x, sprite.getPosition().y), level+1);
        }
    }
    
}

void renderSolarSystem(sf::RenderWindow& window, int system, sf::Vector2f offset, int newZoom)
{
    renderOffset = offset;
    zoom = newZoom;
    if (old)
    {
        sf::Vector2u windowSize = window.getSize();

        int solSize = 100;
        sf::CircleShape sun(solSize);
        sun.setFillColor(galaxy.celestials[galaxy.systems[system].star].color);
        sun.setPosition(-50, windowSize.y/2 - 100);

        window.draw(sun);
        //std::cout << "Draw sun" << std::endl;

        drawCelestials(window, galaxy.systems[system].star, sf::Vector2u(50, windowSize.y/2-50), 0);
    }
    else
    {
        renderTime += 100000;

        drawCelestials(window, galaxy.systems[system].star, sf::Vector2u(renderOffset.x, renderOffset.y), 0);
    }
    
}