#include "destructible.h"
#include <iostream>

Destructible::Destructible(b2World *world, b2BodyType type, const b2Shape* shape, const sf::Vector2f pixelPos, int layer_index, int tile_x, int tile_y)
: layer_index(layer_index), tile_x(tile_x), tile_y(tile_y)
{
    rb = Rigidbody(world, type, shape, pixelPos);
}

void Destructible::setCollisionDetection() {
    rb.setCollisionDetection(this);
}

void Destructible::BeginCollision(b2Contact *contact) {
    to_delete = true;
}

void Destructible::EndCollision(b2Contact *contact) {

}

bool Destructible::update(float delta_time) {
    if (to_delete) {
        delete_cooldown -= delta_time;
        if (delete_cooldown < 0) {
            if (rb.isEnabled()) {
                rb.setEnabled(false);
                return true;
            }
        }
    }
    return false;
}
