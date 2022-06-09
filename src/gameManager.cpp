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

void GameManager::Update(const Camera& camera)
{
    world.Step(timeStep, velocityIterations, positionIterations);
    player.Update(camera.DistanceToPlayer());
    tmxManager.update(camera);
}

void GameManager::Draw(sf::RenderWindow* window, float deltaTime)
{
    player.Animate(deltaTime);
    window->draw(tmxManager);
    window->draw(player.getSprite());
}

void GameManager::HandleInput(sf::Event event)
{
    player.HandleInput(event);
}


void GameManager::Pause()
{
    isPaused = true;
}

void GameManager::Resume()
{
    isPaused = false;
}

bool GameManager::isRunning() const
{
    return !player.isDead() && !isPaused;
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