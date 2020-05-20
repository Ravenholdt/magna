#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "textures.h"

Textures textures;

Textures::Textures(/* args */)
{
    std::string line;
    std::ifstream textureFile ("texture/textures");

    if (textureFile.is_open())
    {
        std::cout << "---------------------------------------" << std::endl;
        while ( getline (textureFile,line) )
        {
            if (line != "textures")
            {
                std::cout << line << std::endl;
                this->textures[line].loadFromFile("texture/" + line);
                this->sprites[line].setTexture(this->textures[line]);

                this->sprites[line].setOrigin(this->textures[line].getSize().x/2, this->textures[line].getSize().y/2);
            }
        }
        textureFile.close();
        std::cout << "Loaded " << this->sprites.size() << " textures." << std::endl;
        std::cout << "---------------------------------------" << std::endl;
    }
}

Textures::~Textures()
{
}

void Textures::init()
{
    
}