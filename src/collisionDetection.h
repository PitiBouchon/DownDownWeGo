#ifndef DOWNDOWNWEGO_COLLISIONDETECTION_H
#define DOWNDOWNWEGO_COLLISIONDETECTION_H

#include "box2d/box2d.h"

class CollisionDetection {
public:
    virtual void BeginCollision(b2Contact *contact) = 0;
    virtual void EndCollision(b2Contact* contact) = 0;
};


#endif //DOWNDOWNWEGO_COLLISIONDETECTION_H
