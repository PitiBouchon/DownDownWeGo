#pragma once
#include <stdio.h>
#include <array>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

enum class State { IDLE, WALK, CLIMB, JUMP, FALL };
enum class Direction { LEFT, RIGHT };

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float baseSpeed;
    float xInput = 0;

    int frame = 0;
    std::array<int, 5> frames = { 4, 6, 4, 8, 8 };
    float animationClock = 0;

    State state = State::IDLE;
    Direction dir = Direction::RIGHT;

    b2Body* body;

public:
    Player(const std::string& image, float baseSpeed, float xpos, float ypos, b2World *world);
    const sf::Sprite& getSprite();

    void UpdateState(sf::Event event);
    void UpdateSpeed();
    void Animate(float deltaTime);
};
