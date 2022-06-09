#pragma once
#include <stdio.h>
#include <array>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "rigidbody.h"
#include "collisionDetection.h"


enum class Command { LEFT, RIGHT, JUMP, GRAB };

enum class States { IDLE, WALK, CLIMB, JUMP, FALL, DEATH };
enum class Direction { LEFT, RIGHT };


class Player : public CollisionDetection {
private:
    const int spriteSize = 32;
    sf::Texture texture;
    sf::Sprite sprite;

    int frame = 0;
    std::array<int, 6> frames = { 4, 6, 4, 8, 4, 8 };
    float animationClock = 0;

    const float MAX_ENDURANCE = 20;
    float endurance = MAX_ENDURANCE;

    const float LETHAL_SPEED = 100;
    const float JUMP_HEIGHT = 12;
    const float BASE_SPEED = 7;
    const float GRAB_SPEED = 0.5;

    float xInput = 0;
    bool onGround = false;
    bool onWall = false;

    Rigidbody rb;

    Direction dir = Direction::RIGHT;
    enum States state = States::IDLE;

    std::map<sf::Keyboard::Key, Command> inputsMap;

public:
    Player(float xpos, float ypos, b2World *world, const std::string& image);
    virtual ~Player() = default;

    sf::Sprite& getSprite();
    void Animate(float deltaTime);
    void ChangeState(States newState);

    void RefillEndurance();
    void Exhaust(float value);
    bool HasEndurance() const;

    void Jump();
    void Land();

    void HandleInput(sf::Event event);
    void HandleKeyPressed(Command command);
    void HandleKeyReleased(Command command);
    void Update(float distanceToCamera);

    void BeginCollision(b2Contact *contact) override;
    void EndCollision(b2Contact* contact) override;

    sf::Vector2f getPosition() const;
    float getVerticalSpeed() const;
    bool isDead() const;
};
