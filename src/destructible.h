#pragma once

#include "collisionDetection.h"
#include "rigidbody.h"

class Destructible : public CollisionDetection {
private:
    Rigidbody rb;
    bool to_delete = false;
    float delete_cooldown = 0.2f;

public:
    int layer_index;
    int tile_x;
    int tile_y;

    Destructible(b2World *world, b2BodyType type, const b2Shape* shape, const sf::Vector2f pixelPos, int layer_index, int tile_x, int tile_y);
    void setCollisionDetection();
    bool update(float delta_time);
    void BeginCollision(b2Contact *contact) override;
    void EndCollision(b2Contact* contact) override;
};
