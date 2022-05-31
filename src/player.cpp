#include <stdio.h>
#include <iostream>
#include "player.h"

using filePath = std::string;

const int spriteSize = 32;

Player::Player(const filePath& image, float baseSpeed, float xpos, float ypos, b2World *world) : baseSpeed(baseSpeed)
{
    // Loading texture
    texture.loadFromFile(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
    sprite.setScale(2, 2);
    sprite.setPosition(xpos, ypos);
    rb = Rigidbody(world, b2_dynamicBody, sprite);
    rb.setCollisionDetection(this);
}

const sf::Sprite & Player::getSprite()
{
    auto textureRect = sf::IntRect(frame * spriteSize, (int) state * spriteSize, spriteSize, spriteSize);
    if (dir == Direction::LEFT)
    {
        textureRect.left += spriteSize;
        textureRect.width = -spriteSize;
    }

    sprite.setTextureRect(textureRect);
    sf::Vector2f pos = rb.getPixelPos();
    sprite.setPosition(pos.x, pos.y);
    sprite.setRotation(rb.getAngle());
    return sprite;
}

void Player::UpdateState(sf::Event event) {
    // Get the xInput (-1 : Left, 0 : Nothing, 1 : Right)
    int factor = event.type == sf::Event::KeyPressed ? 1 : -1;
    if (event.key.code == sf::Keyboard::Right)
    {
        xInput += factor;
    }
    else if (event.key.code == sf::Keyboard::Left)
    {
        xInput -= factor;
    }

    // Update Direction and State
    if (xInput > 0)
    {
        dir = Direction::RIGHT;
        if (state == State::IDLE) state = State::WALK;
    }
    else if (xInput < 0)
    {
        dir = Direction::LEFT;
        if (state == State::IDLE) state = State::WALK;
    }
    else if (state == State::WALK)
    {
        state = State::IDLE;
    }
}

void Player::UpdateSpeed() {
    b2Vec2 vel = rb.getVelocity();
    rb.setVelocity(b2Vec2((float) xInput * baseSpeed, vel.y));
}

void Player::Animate(float deltaTime)
{
    animationClock += deltaTime;
    if (animationClock >= 1.0/frames[(int) state])
    {
        animationClock = 0;
        frame++;
        if (frame >= frames[(int) state]) frame = 0;
    }
}

void Player::BeginCollision(b2Contact *contact)
{
    if (contact->GetManifold()->localNormal.y < 0)
    {
        onGround = true;
    }
}
