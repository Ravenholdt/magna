#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "main.h"
#include "render/solarsystem.h"
#include "render/textures.h"
#include "galaxy.h"

using namespace std;

int createSol()
{
    int sol = galaxy.newSystem();
    int sun = galaxy.systems[sol].star;

    int p;
    p = galaxy.celestials[sun].newChild(5e10, 6e24, 6.4e6); // Mercury
    p = galaxy.celestials[sun].newChild(1e11, 6e24, 6.4e6); // Venus
    p = galaxy.celestials[sun].newChild(1.5e11, 6e24, 6.4e6); // Earth
        p = galaxy.celestials[p].newChild(4e8, 1e10, 1.7e6); // Moon
    p = galaxy.celestials[sun].newChild(2.1e11, 6e24, 6.4e6); // Mars
    p = galaxy.celestials[sun].newChild(7.7e11, 6e24, 6.4e6); // Jupiter
    p = galaxy.celestials[sun].newChild(1.5e12, 6e24, 6.4e6); // Saturn
    p = galaxy.celestials[sun].newChild(3e12, 6e24, 6.4e6); // Uranus
    p = galaxy.celestials[sun].newChild(4.5e12, 6e24, 6.4e6); // Nepture

    return sol;
}

int main()
{
    //textures.init();
    //Celestial* planet = new Celestial(nullptr, 5.972e+24, 1.5068e+8);

    /*bool running = true;
    while (running)
    {
        getchar();
    }*/

    //std::cout << __FILE__ << ": " << __LINE__ << std::endl;

    /*int sol = galaxy.newSystem();
    int sun = galaxy.systems[sol].star;

    //std::cout << __FILE__ << ": " << __LINE__ << std::endl;

    //for (int i = 0 ; i < 3 ; i++)
    galaxy.celestials[sun].newChild(1.5e11, 6e24, 6.4e6);

    galaxy.celestials[galaxy.celestials[sun].childs[0]].newChild(4e8, 1e10, 1.7e6);
    galaxy.celestials[galaxy.celestials[sun].childs[0]].newChild(8e8, 1e10, 1.7e6);
    */

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
    window.setFramerateLimit(60);

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) 
            {
                renderScale*=0.9; 
                std::cout << "Add!" << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
            { 
                renderScale*=1.1; 
                std::cout << "Subtract!" << std::endl;
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                zoom += event.mouseWheel.delta;
            }
        }

        window.clear();
        renderSolarSystem(window, sol, renderOffset, zoom);
        window.display();
        //window.close();
    }

    return 0;
}