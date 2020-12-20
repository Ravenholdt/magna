#include "gui.h"

#include <iostream>

bool gui(sf::RenderWindow& window)
{
    std::cout << "Graphics!" << std::endl;

    return window.isOpen();
}