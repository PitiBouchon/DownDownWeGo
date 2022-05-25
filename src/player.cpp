#include <stdio.h>
#include <iostream>
#include "player.h"

using filePath = std::string;

Player::Player(filePath image, int health, double baseSpeed, double xpos, double ypos, b2World *world) :
     baseSpeed(baseSpeed), health(health)
{
    idle = false;
    xSpeed = 0;
    ySpeed = 0;

    texture.loadFromFile(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setScale(2, 2);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    body = world->CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    body->SetTransform(b2Vec2(xpos, ypos), 0.0f);
}

sf::Sprite Player::getSprite()
{
    sf::IntRect textureRect = sprite.getTextureRect();
    if (idle) textureRect.left = 32;
    else textureRect.left = 0;

    sprite.setTextureRect(textureRect);
    b2Vec2 pos = body->GetPosition();
    sprite.setPosition(pos.x, pos.y);
    return sprite;
}

void Player::Move(sf::Event::KeyEvent key) {

    if (key.code == sf::Keyboard::Right) xSpeed = baseSpeed;
    else if (key.code == sf::Keyboard::Left) xSpeed = -baseSpeed;
    else xSpeed = 0;
}

void Player::UpdatePosition(double deltaTime) {
    b2Vec2 pos = body->GetPosition();
    body->SetTransform(b2Vec2(pos.x + xSpeed * deltaTime, pos.y + ySpeed * deltaTime), body->GetAngle());
}
