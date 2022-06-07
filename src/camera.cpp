#include "camera.h"
#include "player.h"

Camera::Camera(const sf::RenderWindow *window) : view(window->getDefaultView()) {}

void Camera::move(sf::Vector2f dir)
{
    view.move(dir);
}

void Camera::moveTo(sf::Vector2f pos)
{
    view.setCenter(pos);
}

const sf::Vector2f& Camera::getPosition() const
{
    return view.getCenter();
}

const sf::Vector2f& Camera::getSize() const
{
    return view.getSize();
}

sf::Vector2f Camera::getOrigin() const
{
    return sf::Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
}

const sf::View& Camera::getView() const
{
    return view;
}
