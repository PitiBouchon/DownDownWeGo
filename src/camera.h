#ifndef DOWNDOWNWEGO_CAMERA_H
#define DOWNDOWNWEGO_CAMERA_H

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

// https://www.sfml-dev.org/tutorials/2.5/graphics-view.php for more information

class Camera {
private :
    const float fallAcceleration = 1;
    const float maxFallSpeed = 40;
    float fallSpeed = 15;

    const float smoothSpeed = 1.3f;
    const float moveThreshold = 100;

    float distanceToPlayer;
    sf::View view;

public:
    Camera(const sf::RenderWindow *window, float zoom);

    void move(sf::Vector2f dir);
    void moveTo(sf::Vector2f pos);
    void update(float deltaTime, float playerPosition, bool gameRunning);
    
    sf::Vector2f const & getPosition() const;
    sf::Vector2f const & getSize() const;
    sf::Vector2f getOrigin() const;
    sf::Vector2f getCenter() const;
    sf::View const & getView() const;

    float DistanceToPlayer() const;
};


#endif //DOWNDOWNWEGO_CAMERA_H
