#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

class Textures
{
private:
    /* data */
public:
    std::map<std::string, sf::Sprite> sprites;
    std::map<std::string, sf::Texture> textures;

    Textures(/* args */);
    ~Textures();

    void init();
};

extern Textures textures;
