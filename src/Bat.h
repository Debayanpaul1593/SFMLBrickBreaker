#include <SFML/Graphics.hpp>
#include<iostream>
#ifndef BAT_H
#define BAT_H

class Bat : public sf::RectangleShape
{
private:
public:
    Bat();
    ~Bat();
    void slide(float x);
    void initialize();
};

#endif // !BAT_H
