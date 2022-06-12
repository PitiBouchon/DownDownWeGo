#ifndef DOWNDOWNWEGO_MYCONTACTLISTENER_H
#define DOWNDOWNWEGO_MYCONTACTLISTENER_H

#include <iostream>
#include "box2d/box2d.h"
#include "player.h"

/// Contact listener to get all box2d collision information
class MyContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact* contact) override;
};


#endif //DOWNDOWNWEGO_MYCONTACTLISTENER_H
