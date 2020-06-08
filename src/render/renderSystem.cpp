#include <iostream>
#include <string>
#include <math.h>

#include "renderSystem.h"
#include "../galaxy.h"
#include "textures.h"

bool old = false;

RenderSystem renderSystem;

sf::Vector2i RenderSystem::mouseToSystemPos(sf::RenderWindow& window)
{
    sf::Vector2i windowPos =  sf::Mouse::getPosition(window);
    sf::Vector2i systemPos;
    systemPos.x = windowPos.x - (renderOffset.x + renderMouseOffset.x);
    systemPos.y = windowPos.y - (renderOffset.y + renderMouseOffset.y);
    return systemPos;
}

void RenderSystem::zoomToMouse(sf::RenderWindow& window, int zoom)
{
    if (zoom > 0) // Zoom out
    {
        this->renderMouseOffset.x -= mouseToSystemPos(window).x;
        this->renderMouseOffset.y -= mouseToSystemPos(window).y;
    }
    if (zoom < 0) // Zoom in
    {
        this->renderMouseOffset.x += mouseToSystemPos(window).x * 0.5;
        this->renderMouseOffset.y += mouseToSystemPos(window).y * 0.5;
    }
}

void drawCelestialsOld(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level)
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
        drawCelestialsOld(window, galaxy.celestials[galaxy.celestials[celestial].childs[child]].getID(), sf::Vector2i(pos.x, pos.y), level+1);
    }
}

void RenderSystem::drawCelestials(sf::RenderWindow& window, int rendObj, sf::Vector2i pos, int level)
{
    if (old) drawCelestialsOld(window, rendObj, pos, level);
    else
    {
        int celestialID = this->renderObj[rendObj].id;

        int dotSize = 3;
        sf::CircleShape beacon(dotSize);
        beacon.setOrigin(sf::Vector2f(dotSize,dotSize));

        sf::Sprite sprite = textures.sprites[galaxy.celestials[celestialID].sprite];

        sprite.setPosition(sf::Vector2f(this->renderObj[rendObj].pos.x, this->renderObj[rendObj].pos.y));
        float scale = log(galaxy.celestials[celestialID].radius/2) * renderSystem.renderScaleSize;
        sprite.setScale(sf::Vector2f(scale, scale));

        beacon.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
        if (galaxy.celestials[celestialID].type != CelestialType::star) beacon.setFillColor(sf::Color::Cyan);
        window.draw(beacon);
        //window.draw(sprite);

        //renderPos
        
        if (!galaxy.celestials[celestialID].childs.size()) return;

        int numChilds = galaxy.celestials[celestialID].childs.size();

        for(int child = 0 ; child < galaxy.celestials[celestialID].childs.size() ; child++) 
        {
            drawCelestials(window, galaxy.celestials[galaxy.celestials[celestialID].childs[child]].getID(), 
                sf::Vector2i(sprite.getPosition().x, sprite.getPosition().y), level+1);
        }
    }
    
}

void RenderSystem::indexCelestials(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level)
{
    sf::Vector2f celPos(galaxy.celestials[celestial].orbitToPos(renderSystem.renderTime)); 

    if (level)
        pos = sf::Vector2i(pos.x + (celPos.x / renderSystem.renderScaleDistance * std::pow(10, renderSystem.zoom/10)), 
                           pos.y + (celPos.y / renderSystem.renderScaleDistance * std::pow(10, renderSystem.zoom/10)));
    else
        pos = sf::Vector2i(pos.x + celPos.x * renderSystem.renderScaleDistance, pos.y + celPos.y * renderSystem.renderScaleDistance);
    
    sf::Vector2i relPos = sf::Vector2i(pos.x - sf::Mouse::getPosition(window).x, pos.y - sf::Mouse::getPosition(window).y);
    relPos = sf::Vector2i(pow(relPos.x, 2), pow(relPos.y, 2));
    int distToMouse = sqrt(relPos.x + relPos.y);

    renderObject newCel;
    newCel.pos = pos;
    newCel.id = celestial;
    newCel.level = level;
    newCel.distToMouse = distToMouse;
    this->renderObj.push_back(newCel);

    // If the new celestial is closer and "bigger" than the current selected celestial, then replace with the new celestial.
    if (distToMouse < 30 && 
       (level < renderObj[this->mouseHoverOver.x].level || 
       (level = renderObj[this->mouseHoverOver.x].level &&
       distToMouse < renderObj[this->mouseHoverOver.x].distToMouse))) 
       this->mouseHoverOver = sf::Vector2i(renderObj.size() - 1, celestial);

    if (!galaxy.celestials[celestial].childs.size()) return;

    int numChilds = galaxy.celestials[celestial].childs.size();

    for(int child = 0 ; child < galaxy.celestials[celestial].childs.size() ; child++) 
    {
        indexCelestials(window, galaxy.celestials[galaxy.celestials[celestial].childs[child]].getID(), pos, level+1);
    }
    
}


void RenderSystem::renderSolarSystem(sf::RenderWindow& window, int system)
{
    this->renderObj.clear();
    this->renderObj.push_back(renderObject());
    this->mouseHoverOver = sf::Vector2i(0,0);
    sf::Vector2i mpos = renderSystem.mouseToSystemPos(window);
    //std::cout << mpos.x / std::pow(10, renderSystem.zoom/10) << "," << mpos.y / std::pow(10, renderSystem.zoom/10) << std::endl;
    //std::cout << mouseToSystemPos(window).x << "," << mouseToSystemPos(window).y << std::endl;

    if (old)
    {
        sf::Vector2u windowSize = window.getSize();

        int solSize = 100;
        sf::CircleShape sun(solSize);
        sun.setFillColor(galaxy.celestials[galaxy.systems[system].star].color);
        sun.setPosition(-50, windowSize.y/2 - 100);

        window.draw(sun);
        //std::cout << "Draw sun" << std::endl;

        drawCelestials(window, galaxy.systems[system].star, sf::Vector2i(50, windowSize.y/2-50), 0);
    }
    else
    {
        renderSystem.renderTime += 1000;

        indexCelestials(window, galaxy.systems[system].star, sf::Vector2i(this->renderOffset.x + this->renderMouseOffset.x, 
                                                                         this->renderOffset.y + this->renderMouseOffset.y), 0);
        drawCelestials(window, 1, sf::Vector2i(this->renderOffset.x + this->renderMouseOffset.x, 
                                                                         this->renderOffset.y + this->renderMouseOffset.y), 0);
        
        // Render marked celestial
        int dotSize = 3;
        sf::CircleShape beacon(dotSize);
        beacon.setOrigin(sf::Vector2f(dotSize,dotSize));

        int markedObj = this->mouseHoverOver.x;
        beacon.setPosition(sf::Vector2f(this->renderObj[markedObj].pos.x, this->renderObj[markedObj].pos.y));
        beacon.setFillColor(sf::Color::Red);
        window.draw(beacon);

        markedObj = this->mouseSelected.x;
        beacon.setPosition(sf::Vector2f(this->renderObj[markedObj].pos.x, this->renderObj[markedObj].pos.y));
        beacon.setFillColor(sf::Color::Magenta);
        window.draw(beacon);
    }
}