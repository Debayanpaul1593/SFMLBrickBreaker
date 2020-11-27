#include "Bat.h"
sf::Texture batTexture;
Bat::Bat()
{
    //this->initialize();
}
void Bat::initialize()
{
    //load texture for bat
    
    if (!batTexture.loadFromFile("src/res/imgs/pixil_bat_crop.png"))
    {
        std::cout << "Could not load bat texture" << std::endl;
    }
    this->setSize(sf::Vector2f(100, 15));
    this->setPosition(512 - 50, 640 - 20);
    this->setTexture(&batTexture);
}
Bat::~Bat() = default;
void Bat::slide(float x)
{
    this->move(sf::Vector2f(x, 0));
}