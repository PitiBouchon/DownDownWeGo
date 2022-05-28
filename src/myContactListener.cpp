#include "myContactListener.h"

void MyContactListener::BeginContact(b2Contact *contact)
{
    b2BodyUserData userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (CollisionDetection *cd = reinterpret_cast<CollisionDetection*>(userDataA.pointer))
    {
        cd->BeginCollision(contact);
    }

    if (CollisionDetection *cd = reinterpret_cast<CollisionDetection*>(userDataB.pointer))
    {
        cd->BeginCollision(contact);
    }
}
