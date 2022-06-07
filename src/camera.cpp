#include "camera.h"
#include "player.h"
#include <iostream>

Camera::Camera(const sf::RenderWindow *window) : view(window->getDefaultView())
{
    view.zoom(2.0f);
}

void Camera::move(sf::Vector2f dir)
{
    view.move(dir);
}

void Camera::moveTo(sf::Vector2f pos)
{
    view.setCenter(pos);
}

void Camera::update(float playerPosY, float deltaTime)
{
    float distanceToPlayer = playerPosY - getPosition().y + getSize().y / 2;

    if (getSize().y - distanceToPlayer < moveThreshold )
    {
        view.move(0.0f, distanceToPlayer * cameraSmoothSpeed * deltaTime);
    }
    else view.move(0, cameraFallSpeed * deltaTime);
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

sf::Vector2f Camera::getCenter() const
{
    return view.getCenter();
}

const sf::View& Camera::getView() const
{
    return view;
}
