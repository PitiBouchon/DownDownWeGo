#include <iostream>
#include "rigidbody.h"


float toPhysic(float v)
{
    return v / PHYSICS_GRAPHICS_SCALE;
}

float toPixel(float v)
{
    return v * PHYSICS_GRAPHICS_SCALE;
}

void SetBody(b2Body* body, const b2Shape* shape, sf::Vector2f pixelPos)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;

    body->CreateFixture(&fixtureDef);
    body->SetTransform({ toPhysic(pixelPos.x), toPhysic(pixelPos.y) }, 0.0f);
    body->SetFixedRotation(true);
    body->SetLinearDamping(1.0f);
}

Rigidbody::Rigidbody(b2World *world, b2BodyType type, const b2Shape* shape, const sf::Vector2f pixelPos)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;

    body = world->CreateBody(&bodyDef);
    SetBody(body, shape, pixelPos);
}

Rigidbody::Rigidbody(b2World* world, b2BodyType type, const sf::Vector2f shapeSize, const sf::Vector2f pixelPos)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(toPhysic(shapeSize.x / 2), toPhysic(shapeSize.y / 2));

    SetBody(body, &dynamicBox, pixelPos);
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
