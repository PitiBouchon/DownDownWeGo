#include "rigidbody.h"

extern const float PHYSICS_GRAPHICS_SCALE;

b2Vec2 toPhysicsPos(sf::Vector2f pixelPos)
{
    return b2Vec2(pixelPos.x / PHYSICS_GRAPHICS_SCALE, pixelPos.y / PHYSICS_GRAPHICS_SCALE);
}

sf::Vector2f toPixelPos(b2Vec2 physicPos)
{
    return sf::Vector2f(physicPos.x * PHYSICS_GRAPHICS_SCALE, physicPos.y * PHYSICS_GRAPHICS_SCALE);
}

Rigidbody::Rigidbody(b2World *world, b2BodyType type, b2PolygonShape shape, sf::Vector2f pixelPos)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;

    body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    body->SetTransform(toPhysicsPos(pixelPos), 0.0f);
}

Rigidbody::Rigidbody(b2World *world, b2BodyType type, sf::Sprite image)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;

    body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(image.getLocalBounds().width / PHYSICS_GRAPHICS_SCALE, image.getLocalBounds().height / PHYSICS_GRAPHICS_SCALE);

    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    body->SetTransform(toPhysicsPos(image.getPosition()), 0.0f);
}

//Rigidbody::Rigidbody(b2World *world, b2BodyType type, b2PolygonShape shape, sf::Vector2f pixelPos)
//{
//    b2BodyDef bodyDef;
//    bodyDef.type = type;
//
//    Rigidbody(world, bodyDef, shape, pixelPos);
//}

const sf::Vector2f Rigidbody::getPixelPos()
{
    auto pos = body->GetPosition();
    return sf::Vector2f(pos.x * PHYSICS_GRAPHICS_SCALE, pos.y * PHYSICS_GRAPHICS_SCALE);
}

const b2Vec2 Rigidbody::getPhysicPos()
{
    return body->GetPosition();
}

const b2Vec2 Rigidbody::getVelocity()
{
    return body->GetLinearVelocity();
}

void Rigidbody::setVelocity(const b2Vec2 &vel)
{
    body->SetLinearVelocity(vel);
}
