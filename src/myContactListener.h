#ifndef DOWNDOWNWEGO_MYCONTACTLISTENER_H
#define DOWNDOWNWEGO_MYCONTACTLISTENER_H

#include <iostream>
#include "box2d/box2d.h"
#include "player.h"

class MyContactListener : public b2ContactListener {
public:
//    MyContactListener() = default;
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact* contact) override;
};


#endif //DOWNDOWNWEGO_MYCONTACTLISTENER_H
