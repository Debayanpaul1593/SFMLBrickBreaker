#include "Ball.h"
Ball::Ball()
{
}
sf::Texture ballTexture;
Ball::~Ball() = default;

void Ball::initialize()
{
    //load texture for ball
    if (!ballTexture.loadFromFile("src/res/imgs/ball_pixel_crop.png"))
    {
        std::cout << "Could not load ball texture!" << std::endl;
    }
    this->setRadius(10.f);
    //ball.setFillColor(sf::Color::Yellow);
    this->setPosition(512, 640 - 25 - 15);
    this->setTexture(&ballTexture);
}