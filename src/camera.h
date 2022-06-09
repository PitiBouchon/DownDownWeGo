#ifndef DOWNDOWNWEGO_CAMERA_H
#define DOWNDOWNWEGO_CAMERA_H

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

// https://www.sfml-dev.org/tutorials/2.5/graphics-view.php for more information

class Camera {
private :
    const float fallAcceleration = 2.5;
    const float maxFallSpeed = 500;
    float fallSpeed = 50;

    const float smoothSpeed = 1.3f;
    const float moveThreshold = 300;

    float distanceToPlayer = 0;
    sf::View view;

public:
    Camera() = default;
    void SetWindow(const sf::RenderWindow* window, float zoom);

    void move(sf::Vector2f dir);
    void moveTo(sf::Vector2f pos);
    void update(float deltaTime, float playerPosition, bool gameRunning);
    
    sf::Vector2f const & getPosition() const;
    sf::Vector2f const & getSize() const;
    sf::Vector2f getOrigin() const;
    sf::Vector2f getCenter() const;
    sf::View const & getView() const;

    float DistanceToPlayer() const;

    //For debug
    float FallSpeed() const;
};


#endif //DOWNDOWNWEGO_CAMERA_H
