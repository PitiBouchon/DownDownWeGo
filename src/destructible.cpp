#include "destructible.h"
#include <iostream>

Destructible::Destructible(b2World *world, b2BodyType type, const b2Shape* shape, const sf::Vector2f pixelPos, int layer_index, int tile_x, int tile_y)
: layer_index(layer_index), tile_x(tile_x), tile_y(tile_y)
{
    rb = Rigidbody(world, type, shape, pixelPos);
    std::cout << "setCollisionDetection Destructible !" << std::endl;
//    rb.setCollisionDetection(this);
}

void Destructible::setCollisionDetection() {
    rb.setCollisionDetection(this);
}

void Destructible::BeginCollision(b2Contact *contact) {
    std::cout << "Contact !" << std::endl;
    to_delete = true;
    std::cout << "End BeginContact !" << std::endl;
}

void Destructible::EndCollision(b2Contact *contact) {
    std::cout << "EndCollision !" << std::endl;
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
