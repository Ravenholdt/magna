#include <iostream>
#include <string>
#include <math.h>

#include "renderSystem.h"
#include "../galaxy.h"
#include "textures.h"

bool old = false;

sf::Vector2f globalRenderOffset;

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
    sf::Vector2i pos = mouseToSystemPos(window);

    if (zoom > 0) // Zoom out
    {
        this->renderOffset.x -= pos.x * zoom; //std::pow(10, renderSystem.zoom/10);
        this->renderOffset.y -= pos.y * zoom; //std::pow(10, renderSystem.zoom/10);
    }
    if (zoom < 0) // Zoom in
    {
        this->renderOffset.x += pos.x / std::pow(10, renderSystem.zoom/10);
        this->renderOffset.y += pos.y / std::pow(10, renderSystem.zoom/10);
    }
}

void RenderSystem::zoomToCelestial(int zoom)
{
    sf::Vector2f pos = galaxy.celestials[selected.selected.y].orbitToPosSystem(renderSystem.renderTime);

    if (zoom > 0) // Zoom out
    {
        this->renderOffset.x -= pos.x;
        this->renderOffset.y -= pos.y;
    }
    if (zoom < 0) // Zoom in
    {
        this->renderOffset.x += pos.x * 0.5;
        this->renderOffset.y += pos.y * 0.5;
    }
}

void drawCelestialsOld(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level)
{
    if (galaxy.celestials[celestial].parent)
    {
        sf::Sprite sprite = textures.sprites[galaxy.celestials[celestial].sprite];
        sprite.setPosition(pos.x, pos.y);
        float mass = galaxy.celestials[celestial].mass;
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
        window.draw(sprite);

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

sf::Vector2f RenderSystem::getCelestialScreenPos(int celestial)
{
    sf::Vector2f pos = galaxy.celestials[celestial].orbitToPosSystem(renderSystem.renderTime);
    pos.x  = pos.x / renderSystem.renderScaleDistance * zoom; //std::pow(10, renderSystem.zoom/10);
    pos.y  = pos.y / renderSystem.renderScaleDistance * zoom; //std::pow(10, renderSystem.zoom/10);

    pos.x = renderOffset.x - pos.x;
    pos.y = renderOffset.y - pos.y;

    return pos;
}

void RenderSystem::indexCelestials(sf::RenderWindow& window, int celestial, sf::Vector2i pos, int level)
{
    sf::Vector2f celPos(galaxy.celestials[celestial].orbitToPosParent(renderSystem.renderTime)); 

    if (level)
        pos = sf::Vector2i(pos.x + (celPos.x / renderSystem.renderScaleDistance * zoom), //std::pow(10, renderSystem.zoom/10)), 
                           pos.y + (celPos.y / renderSystem.renderScaleDistance * zoom)); //std::pow(10, renderSystem.zoom/10)));
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
       (level < renderObj[selected.hover.x].level || 
       (level = renderObj[selected.hover.x].level &&
       distToMouse < renderObj[selected.hover.x].distToMouse))) 
       selected.hover = sf::Vector2i(renderObj.size() - 1, celestial);

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
    this->selected.hover = sf::Vector2i(0,0);
    sf::Vector2i mpos = renderSystem.mouseToSystemPos(window);
    //std::cout << mpos.x / std::pow(10, renderSystem.zoom/10) << "," << mpos.y / std::pow(10, renderSystem.zoom/10) << std::endl;
    //std::cout << mouseToSystemPos(window).x << "," << mouseToSystemPos(window).y << std::endl;

    /*if (mouseSelected != sf::Vector2i(0,0) && mouseSelectedLastOffset != sf::Vector2f(0,0))
    {
        sf::Vector2f pos = getCelestialScreenPos(mouseSelected.y);

        this->renderOffset.x -= pos.x - mouseSelectedLastOffset.x;
        this->renderOffset.y -= pos.y - mouseSelectedLastOffset.y;
    }*/

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
        renderSystem.renderTime = galaxy.tick;

        indexCelestials(window, galaxy.systems[system].star, sf::Vector2i(this->renderOffset.x + this->renderMouseOffset.x, 
                                                                         this->renderOffset.y + this->renderMouseOffset.y), 0);
        drawCelestials(window, 1, sf::Vector2i(this->renderOffset.x + this->renderMouseOffset.x, 
                                                                         this->renderOffset.y + this->renderMouseOffset.y), 0);
        
        // Render marked celestial
        int dotSize = 3;
        sf::CircleShape beacon(dotSize);
        beacon.setOrigin(sf::Vector2f(dotSize,dotSize));

        // Hover over
        int markedObj = this->selected.hover.x;
        beacon.setPosition(sf::Vector2f(this->renderObj[markedObj].pos.x, this->renderObj[markedObj].pos.y));
        beacon.setFillColor(sf::Color::Red);
        window.draw(beacon);

        // Selected
        markedObj = this->selected.selected.x;
        beacon.setPosition(sf::Vector2f(this->renderObj[markedObj].pos.x, this->renderObj[markedObj].pos.y));
        beacon.setFillColor(sf::Color::Magenta);
        window.draw(beacon);
    }

    if (selected.selected != sf::Vector2i(0,0)) selected.mouseSelectedLastOffset = getCelestialScreenPos(selected.selected.y);
}