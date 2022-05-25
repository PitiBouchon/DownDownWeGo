#include <stdio.h>
#include <iostream>
#include "player.h"

using filePath = std::string;

const int spriteSize = 32;

Player::Player(const filePath& image, float baseSpeed, float xpos, float ypos, b2World *world) :
     baseSpeed(baseSpeed)
{
    //Loading texture
    texture.loadFromFile(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
    sprite.setScale(4, 4);

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
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    body->SetTransform(b2Vec2(xpos, ypos), 0.0f);
}

sf::Sprite Player::getSprite()
{
    auto textureRect = sf::IntRect(frame * spriteSize, (int) state * spriteSize, spriteSize, spriteSize);
    if (dir == Direction::LEFT)
    {
        textureRect.left += spriteSize;
        textureRect.width = -spriteSize;
    }

    sprite.setTextureRect(textureRect);
    b2Vec2 pos = body->GetPosition();
    sprite.setPosition(pos.x, pos.y);
    return sprite;
}

void Player::Move(sf::Event::KeyEvent key) {

    std::cout << key.code << std::endl;

    if (key.code == sf::Keyboard::Right)
    {
        xSpeed = baseSpeed;
        state = State::WALK;
        dir = Direction::RIGHT;
    }
    else if (key.code == sf::Keyboard::Left)
    {
        xSpeed = -baseSpeed;
        state = State::WALK;
        dir = dir = Direction::LEFT;
    }
    else
    {
        xSpeed = 0;
        state = State::IDLE;
    }
}

void Player::UpdatePosition(float deltaTime) {
    b2Vec2 pos = body->GetPosition();
    body->SetTransform(b2Vec2(pos.x + xSpeed * deltaTime, pos.y + ySpeed * deltaTime), body->GetAngle());
}

void Player::Animate(float deltaTime)
{
    animationClock += deltaTime;
    if (animationClock >= 1/animationFrequency)
    {
        animationClock = 0;
        frame++;
        if (frame >= frames[(int) state]) frame = 0;
    }
}