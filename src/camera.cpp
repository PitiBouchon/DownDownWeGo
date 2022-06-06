#include "camera.h"
#include "player.h"

Camera::Camera(sf::RenderWindow *window) {
    view = window->getDefaultView();
//    sf::Vector2<unsigned int> window_size = window->getSize();
//    view.setSize((float) window_size.x, (float) window_size.y);
//    view.setCenter((float) window_size.x / 2, (float) window_size.y / 2); // Center the view
//    view.zoom(0.5f);
}

void Camera::move(sf::Vector2f dir)
{
    view.move(dir);
}

void Camera::moveTo(sf::Vector2f pos)
{
    view.setCenter(pos);
}

const sf::Vector2f &Camera::getPosition() const
{
    return view.getCenter();
}

const sf::Vector2f &Camera::getSize() const
{
    return view.getSize();
}

const sf::View &Camera::getView()
{
    return view;
}
