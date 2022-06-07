#include <stdio.h>
#include <iostream>
#include "player.h"


using filePath = std::string;
const int spriteSize = 32;

Player::Player(float xpos, float ypos, b2World *world, const filePath& image)
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

void Player::Animate(float deltaTime)
{
    animationClock += deltaTime;
    if (animationClock >= 1.0 / frames[(int)state])
    {
        animationClock = 0;
        frame++;
        if (frame >= frames[(int)state]) frame = 0;
    }
}

void Player::ChangeState(States newState)
{
    if (newState == state) return;

    frame = 0;
    state = newState;

    switch (state) {
    case States::IDLE: std::cout << "IDLE\n"; break;
    case States::WALK: std::cout << "WALK\n"; break;
    case States::CLIMB: std::cout << "CLIMB\n"; break;
    case States::JUMP: std::cout << "JUMP\n"; break;
    case States::FALL: std::cout << "FALL\n"; break;
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
    else if (command == Command::GRAB && HasEndurance())
    {
        onGround = true;
        ChangeState(States::CLIMB);
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
        ChangeState(States::FALL);
    }
}


void Player::Update()
{
    
    b2Vec2 b2Velocity = rb.getVelocity();
    if (state == States::CLIMB)
    {
        rb.setVelocity(b2Vec2(0, std::min(b2Velocity.y, GRAB_SPEED)));
        Exhaust(0.1);
        if (!HasEndurance())
        {  
            std::cout << "No Endurance!\n";
            ChangeState(States::FALL);
        }
    }
    else
    {
        rb.setVelocity(b2Vec2(xInput * BASE_SPEED, b2Velocity.y));
        
        if (b2Velocity.y == 0) { if (!onGround) Land(); }
        else ChangeState(States::FALL);
    }
}


void Player::BeginCollision(b2Contact *contact)
{
    if (contact->GetManifold()->localNormal.y > 0)
    {
        if (rb.getVelocity().y >= LETHAL_SPEED)
        {
            // Die here
            printf("PLAYER IS DEAD !\n");
        }

        Land();
    }
}
