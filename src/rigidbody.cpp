#include <iostream>
#include "rigidbody.h"

//const float PHYSICS_GRAPHICS_SCALE = 30.0f; // 1m = 30 pixels

float toPhysic(float v)
{
    return v / PHYSICS_GRAPHICS_SCALE;
}

float toPixel(float v)
{
    return v * PHYSICS_GRAPHICS_SCALE;
}

Rigidbody::Rigidbody(b2World *world, b2BodyType type, const b2Shape *shape, sf::Vector2f pixelPos)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;

    body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;

    body->CreateFixture(&fixtureDef);
    body->SetTransform({toPhysic(pixelPos.x), toPhysic(pixelPos.y)}, 0.0f);
    body->SetFixedRotation(true);
    body->SetLinearDamping(1.0f);
}

Rigidbody::Rigidbody(b2World *world, b2BodyType type, const sf::Sprite& image)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;

    body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(toPhysic(image.getGlobalBounds().width / 2), toPhysic(image.getGlobalBounds().height / 2));

    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;

    body->CreateFixture(&fixtureDef);

    offset = b2Vec2(toPhysic((image.getLocalBounds().width - image.getGlobalBounds().width) / 2.0f), toPhysic((image.getLocalBounds().height - image.getGlobalBounds().height) / 2.0f));
    body->SetTransform({toPhysic(image.getPosition().x), toPhysic(image.getPosition().y)}, image.getRotation());
    body->SetFixedRotation(true);
    body->SetLinearDamping(1.0f);
}

sf::Vector2f Rigidbody::getPixelPos() const
{
    auto pos = body->GetPosition() + offset;
    return sf::Vector2f(toPixel(pos.x), toPixel(pos.y));
}

b2Vec2 Rigidbody::getPhysicPos() const
{
    return body->GetPosition() + offset;
}

const b2Vec2 &Rigidbody::getVelocity() const
{
    return body->GetLinearVelocity();
}

float Rigidbody::getAngle() const
{
    return body->GetAngle();
}

void Rigidbody::setVelocity(const b2Vec2 &vel)
{
    body->SetLinearVelocity(vel);
}

void Rigidbody::setCollisionDetection(CollisionDetection *cd)
{
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(cd);
}

void Rigidbody::addImpulse(b2Vec2 impulse)
{
    body->ApplyLinearImpulseToCenter(impulse, true);
}
