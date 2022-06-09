#include <stdio.h>
#include <iostream>
#include "player.h"

Player::Player(float xpos, float ypos, b2World *world, const std::string& image)
{
    // Loading texture
    texture.loadFromFile(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
    sprite.setPosition(xpos, ypos);

    //Setting default inputs
    inputsMap[sf::Keyboard::Left] = Command::LEFT;
    inputsMap[sf::Keyboard::Right] = Command::RIGHT;
    inputsMap[sf::Keyboard::Up] = Command::JUMP;
    inputsMap[sf::Keyboard::Space] = Command::GRAB;

    //Creating rigidbody
    auto rbSize = sf::Vector2f(0.5f * spriteSize, 0.9f * spriteSize);
    rb = Rigidbody(world, b2_dynamicBody, rbSize, sprite.getPosition());
    rb.setCollisionDetection(this);
}

sf::Sprite& Player::getSprite()
{
    auto textureRect = sf::IntRect(frame * spriteSize, (int)state * spriteSize, spriteSize, spriteSize);
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

void Player::Animate(float deltaTime)
{
    animationClock += deltaTime;
    if (animationClock >= 1.0 / frames[(int)state])
    {
        animationClock = 0;
        frame++;
        if (frame >= frames[(int)state] && state != States::DEATH) frame = 0;
    }
}

void Player::ChangeState(States newState)
{
    if (newState == state || state == States::DEATH) return;

    frame = 0;
    state = newState;
    
    switch (state) {
    case States::IDLE: std::cout << "IDLE\n"; break;
    case States::WALK: std::cout << "WALK\n"; break;
    case States::CLIMB: std::cout << "CLIMB\n"; break;
    case States::JUMP: std::cout << "JUMP\n"; break;
    case States::FALL: std::cout << "FALL\n"; break;
    case States::DEATH: std::cout << "DEATH\n"; break;
    default: std::cout << "ERROR\n"; break;
    }
}

void Player::RefillEndurance() {
    endurance = MAX_ENDURANCE;
}

void Player::Exhaust(float value) {
    endurance -= value;
}

bool Player::HasEndurance() const {
    return (endurance > 0);
}


void Player::Jump()
{
    if (onGround)
    {
        rb.addImpulse(b2Vec2(0, -JUMP_HEIGHT));
        onGround = false;
        ChangeState(States::JUMP);
    }
}

void Player::Land()
{
    onGround = true;
    if (xInput == 0) ChangeState(States::IDLE);
    else ChangeState(States::WALK);

    RefillEndurance();
}

void Player::HandleInput(sf::Event event)
{
    if (!inputsMap.contains(event.key.code)) return;
    Command command = inputsMap[event.key.code];

    if (event.type == sf::Event::KeyPressed) HandleKeyPressed(command);
    if (event.type == sf::Event::KeyReleased) HandleKeyReleased(command);
}

void Player::HandleKeyPressed(Command command)
{
    if (command == Command::RIGHT)
    {
        xInput = 1;
        dir = Direction::RIGHT;
        if (state == States::IDLE) ChangeState(States::WALK);
    }
    else if (command == Command::LEFT)
    {
        xInput = -1;
        dir = Direction::LEFT;
        if (state == States::IDLE) ChangeState(States::WALK);
    }
    else if (command == Command::JUMP)
    {
        Jump();
    }
    else if (command == Command::GRAB)
    {
        grabbing = true;
    }
}

void Player::HandleKeyReleased(Command command)
{
    if (command == Command::RIGHT || command == Command::LEFT)
    {
        xInput = 0;
        if (state == States::WALK) ChangeState(States::IDLE);
    }
    else if (command == Command::GRAB)
    {
        grabbing = false;
        ChangeState(States::FALL);
        onGround = false;
    }
}


void Player::Update(float distanceToCamera)
{
    b2Vec2 b2Velocity = rb.getVelocity();

    if (grabbing && HasEndurance() && onWall)
    {
        onGround = true;
        ChangeState(States::CLIMB);
    }

    if (state == States::CLIMB)
    {
        rb.setVelocity(b2Vec2(0, std::min(b2Velocity.y, GRAB_SPEED)));
        Exhaust(0.1f);
        if (!HasEndurance())
        {  
            std::cout << "No Endurance!\n";
            ChangeState(States::FALL);
        }
        if (!onWall)
        {
            std::cout << "No Wall!\n";
            ChangeState(States::FALL);
        }
    }
    else
    {
        rb.setVelocity(b2Vec2(xInput * BASE_SPEED, b2Velocity.y));

        if (b2Velocity.y == 0) { if (!onGround) Land(); }
        else
        {
            ChangeState(States::FALL);
            onGround = false;
        }
    }

    if (distanceToCamera < 0) ChangeState(States::DEATH);
}


void Player::BeginCollision(b2Contact *contact)
{
    if (contact->GetManifold()->localNormal.y > 0)
    {
        std::cout << rb.getVelocity().y << std::endl;
        if (rb.getVelocity().y >= LETHAL_SPEED)
        {
            ChangeState(States::DEATH);
        }
        else Land();
    }

    if (contact->GetManifold()->localNormal.x != 0)
    {
        std::cout << "Touching Wall\n";
        onWall = true;
    }
}

void Player::EndCollision(b2Contact* contact)
{
    //Note: you could replace our State shenanigans in Update by putting something here:
    /*
    if (contact->GetManifold()->localNormal.y > 0)
    {
        FALL or something, idk
    }
    */

    if (contact->GetManifold()->localNormal.x != 0)
    {
        std::cout << "Not touching Wall anymore\n";
        onWall = false;
    }
}


sf::Vector2f Player::getPosition() const
{
    return rb.getPixelPos();
}

float Player::getVerticalSpeed() const
{
    return rb.getVelocity().y;
}

bool Player::isDead() const
{
    return state == States::DEATH;
}