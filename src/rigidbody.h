#ifndef DOWNDOWNWEGO_RIGIDBODY_H
#define DOWNDOWNWEGO_RIGIDBODY_H

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "collisionDetection.h"

const float PHYSICS_GRAPHICS_SCALE = 30.0f; // 1m = 30 pixels

class Rigidbody {
private:
    b2Body* body{};
public:
    Rigidbody() = default;
    Rigidbody(b2World *world, b2BodyType type, sf::Sprite image);
    Rigidbody(b2World *world, b2BodyType type, b2PolygonShape shape, sf::Vector2f pixelPos);
    const sf::Vector2f getPixelPos();
    const b2Vec2 &getPhysicPos();
    const b2Vec2 &getVelocity();
    void setVelocity(const b2Vec2 &vel);
    void setCollisionDetection(CollisionDetection *cd);
};


#endif //DOWNDOWNWEGO_RIGIDBODY_H
