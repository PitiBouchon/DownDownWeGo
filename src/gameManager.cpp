#include "gameManager.h"
#include "myContactListener.h"

const std::string absolutePath = "C:/Users/clemence/Documents/Travail/TSP/CSC4526_Cpp/Projet/DownDownWeGo/";

GameManager::GameManager(float timeStep) :
    timeStep(timeStep),
    world(b2Vec2(0.0f, GRAVITY)),
    tmxManager(absolutePath + "resources/maps/", &world),
    player(tmxManager.getMapWidth() / 2, tmxManager.getMapHeight() * 3, &world, "resources/player_spritesheet.png")
{
    world.SetContactListener(&listener);
}

void GameManager::Step()
{
    world.Step(timeStep, velocityIterations, positionIterations);
}

void GameManager::Update(float deltaTime, const Camera& camera)
{
    player.Update();
    player.Animate(deltaTime);
    tmxManager.update(camera);
}

void GameManager::Draw(sf::RenderWindow* window)
{
    window->draw(tmxManager);
    window->draw(player.getSprite());
}

void GameManager::HandleInput(sf::Event event)
{
    player.HandleInput(event);
}


float GameManager::getMapWidth() const
{
    return tmxManager.getMapWidth();
}

float GameManager::getMapHeight() const
{
    return tmxManager.getMapHeight();
}

float GameManager::PlayerYPos() const
{
    return player.getPosition().y;
}

float GameManager::PlayerYSpeed() const
{
    return player.getVerticalSpeed();
}