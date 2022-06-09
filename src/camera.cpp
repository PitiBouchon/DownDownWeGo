#include "camera.h"
#include "player.h"
#include <iostream>

Camera::Camera(const sf::RenderWindow *window, float zoom) : view(window->getDefaultView())
{
    view.setSize(sf::Vector2f(window->getSize()));
    view.setCenter(sf::Vector2f(window->getSize().x / (2 * zoom), window->getSize().y));
    view.zoom(1.0f / zoom);
}

void Camera::move(sf::Vector2f dir)
{
    view.move(dir);
}

void Camera::moveTo(sf::Vector2f pos)
{
    view.setCenter(pos);
}

void Camera::update(float deltaTime, float playerPosY, bool gameRunning)
{
    fallSpeed += fallAcceleration * deltaTime;
    if (fallSpeed > maxFallSpeed) fallSpeed = maxFallSpeed;

    distanceToPlayer = playerPosY - getPosition().y + getSize().y / 2;

    if (getSize().y - distanceToPlayer < moveThreshold )
    {
        view.move(0.0f, distanceToPlayer * smoothSpeed * deltaTime);
    }
    else if (gameRunning) view.move(0, fallSpeed * deltaTime);
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

float Camera::DistanceToPlayer() const
{
    return distanceToPlayer;
}