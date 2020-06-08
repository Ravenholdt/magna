#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "main.h"
#include "render/renderSystem.h"
#include "render/textures.h"
#include "galaxy.h"

using namespace std;

int createSol()
{
    int sol = galaxy.newSystem();
    int sun = galaxy.systems[sol].star;

    int p;
    p = galaxy.celestials[sun].newChild(5e10, 6e24, 6.4e6, CelestialType::planet); // Mercury
    p = galaxy.celestials[sun].newChild(1e11, 6e24, 6.4e6, CelestialType::planet); // Venus
    p = galaxy.celestials[sun].newChild(1.5e11, 6e24, 6.4e6, CelestialType::planet); // Earth
        galaxy.celestials[p].newChild(4e8, 1e10, 1.7e6, CelestialType::moon); // Moon
    p = galaxy.celestials[sun].newChild(2.1e11, 6e24, 6.4e6, CelestialType::planet); // Mars
        galaxy.celestials[p].newChild(9.4e6, 1e16, 1.1e4, CelestialType::moon); // Phobos
        galaxy.celestials[p].newChild(2.3e7, 1.5e15, 6.2e3, CelestialType::moon); // Deimos
    p = galaxy.celestials[sun].newChild(7.7e11, 6e24, 6.4e6, CelestialType::planet); // Jupiter
    p = galaxy.celestials[sun].newChild(1.5e12, 6e24, 6.4e6, CelestialType::planet); // Saturn
    p = galaxy.celestials[sun].newChild(3e12, 6e24, 6.4e6, CelestialType::planet); // Uranus
    p = galaxy.celestials[sun].newChild(4.5e12, 6e24, 6.4e6, CelestialType::planet); // Nepture

    return sol;
}

int main()
{
    int sol = createSol();

    for (int i = 1 ; i <= galaxy.celestials.size() ; i++)
    {
        std::cout << galaxy.celestials[i].parent << " <- " << galaxy.celestials[i].getID() << std::endl;
    }

    //std::cout << __FILE__ << ": " << __LINE__ << std::endl;

    int windowHeight = sf::VideoMode::getDesktopMode().height;
    int windowWidth = sf::VideoMode::getDesktopMode().width;

    sf::Vector2f renderOffset = sf::Vector2f(windowWidth/2, windowHeight/2);
    float renderScale = 1;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Magna"/*, sf::Style::Fullscreen*/);
    //window.setFramerateLimit(60);

    std::cout << "Begin" << std::endl;

    int zoom = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) renderOffset.y+=10;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) renderOffset.y-=10;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) renderOffset.x+=10;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) renderOffset.x-=10;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                renderSystem.mouseSelected = renderSystem.mouseHoverOver;
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                renderSystem.zoom += event.mouseWheel.delta;
                renderSystem.zoomToMouse(window, event.mouseWheel.delta);
            }
        }

        window.clear();
        renderSystem.renderOffset = renderOffset;
        renderSystem.renderSolarSystem(window, sol);
        window.display();
    }

    return 0;
}