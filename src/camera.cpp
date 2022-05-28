#include "camera.h"

Camera::Camera(sf::RenderWindow *window)
{
    sf::Vector2<unsigned int> window_size = window->getSize();
    view.setSize((float) window_size.x, (float) window_size.y);
    view.setCenter((float) window_size.x / 2, (float) window_size.y / 2); // Center the view
}

void Camera::move(sf::Vector2f dir)
{
    view.move(dir);
}

const sf::View &Camera::getView()
{
    return view;
}
