#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    double baseSpeed;

public:
    int health;
    bool idle;

    double x_pos;
    double y_pos;
    double xSpeed;
    double ySpeed;

    Player(std::string image, int health, double baseSpeed, double xpos, double ypos);
    sf::Sprite getSprite();

    void Move(sf::Event::KeyEvent key);
    void UpdatePosition(double deltaTime);

};