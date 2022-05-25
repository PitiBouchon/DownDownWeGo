#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    double baseSpeed;

    b2Body* body;

public:
    int health;
    bool idle;

//    double x_pos;
//    double y_pos;
    double xSpeed;
    double ySpeed;

    Player(std::string image, int health, double baseSpeed, double xpos, double ypos, b2World *world);
    sf::Sprite getSprite();

    void Move(sf::Event::KeyEvent key);
    void UpdatePosition(double deltaTime);

};