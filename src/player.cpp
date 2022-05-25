#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

using filePath = std::string;

Player::Player(filePath image, int health, double baseSpeed, double xpos, double ypos) :
     baseSpeed(baseSpeed), health(health), x_pos(xpos), y_pos(ypos)
{
    idle = false;
    xSpeed = 0;
    ySpeed = 0;

    texture.loadFromFile(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setScale(2, 2);
}

sf::Sprite Player::getSprite()
{
    sf::IntRect textureRect = sprite.getTextureRect();
    if (idle) textureRect.left = 32;
    else textureRect.left = 0;

    sprite.setTextureRect(textureRect);
    sprite.setPosition(x_pos, y_pos);
    return sprite;
}

void Player::Move(sf::Event::KeyEvent key) {

    if (key.code == sf::Keyboard::Right) xSpeed = baseSpeed;
    else if (key.code == sf::Keyboard::Left) xSpeed = -baseSpeed;
    else xSpeed = 0;
}

void Player::UpdatePosition(double deltaTime) {
    x_pos += xSpeed * deltaTime;
    y_pos += ySpeed * deltaTime;
}