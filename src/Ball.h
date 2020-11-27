#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef BALL_H
#define BALL_H
class Ball : public sf::CircleShape
{
public:
    Ball();

    ~Ball();

    void initialize();
};

#endif // !BALL_H