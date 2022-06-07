#ifndef DOWNDOWNWEGO_CAMERA_H
#define DOWNDOWNWEGO_CAMERA_H

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

// https://www.sfml-dev.org/tutorials/2.5/graphics-view.php for more information

class Camera {
private :
    const float cameraSmoothSpeed = 1.3f;
    const float cameraFallSpeed = 100;
    const float moveThreshold = 100;

public:
    sf::View view;

    Camera(const sf::RenderWindow *window);

    void move(sf::Vector2f dir);
    void moveTo(sf::Vector2f pos);
    void update(float playerPosition, float deltaTime);
    
    sf::Vector2f const & getPosition() const;
    sf::Vector2f const & getSize() const;
    sf::Vector2f getOrigin() const;
    sf::Vector2f getCenter() const;
    sf::View const & getView() const;
};


#endif //DOWNDOWNWEGO_CAMERA_H
