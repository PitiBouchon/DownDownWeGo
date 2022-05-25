#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

enum class State { IDLE, WALK, CLIMB, JUMP, FALL };
enum class Direction { LEFT, RIGHT };

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float baseSpeed;
    float xSpeed = 0;
    float ySpeed = 0;

    int frame = 0;
    int frames[5] = { 4, 6, 4, 8, 8 };

    float animationFrequency = 1;
    float animationClock = 0;

    State state = State::IDLE;
    Direction dir = Direction::RIGHT;

    b2Body* body;

public:
    Player(const std::string& image, float baseSpeed, float xpos, float ypos, b2World *world);
    sf::Sprite getSprite();

    void Move(sf::Event::KeyEvent key);
    void UpdatePosition(float deltaTime);
    void Animate(float deltaTime);
};
