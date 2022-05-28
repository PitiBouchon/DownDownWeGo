#ifndef DOWNDOWNWEGO_CAMERA_H
#define DOWNDOWNWEGO_CAMERA_H

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

class Camera {
private:
    // https://www.sfml-dev.org/tutorials/2.5/graphics-view.php for more information
    sf::View view;
public:
    Camera(sf::RenderWindow *window);
    void move(sf::Vector2f dir);
    const sf::View & getView();
};


#endif //DOWNDOWNWEGO_CAMERA_H
