#include "gameManager.h"
#include "myContactListener.h"

const std::string absolutePath = "C:/Users/clemence/Documents/Travail/TSP/CSC4526_Cpp/Projet/DownDownWeGo/";

GameManager::GameManager(float cameraZoom, int maxFps) :
    timeStep(1.0f/maxFps),
    world(b2Vec2(0.0f, GRAVITY)),
    tmxManager(absolutePath + "resources/maps/", &world),
    player(tmxManager.getMapWidth() / 2, tmxManager.getMapHeight() * 3, &world, "resources/player_spritesheet.png"),
    cameraZoom(cameraZoom),
    MAX_FPS(maxFps)
{
    world.SetContactListener(&listener);
}

void GameManager::SetWindow(sf::RenderWindow* window_p)
{
    window = window_p;
    camera.SetWindow(window, cameraZoom);
}


void GameManager::Update()
{
    world.Step(timeStep, velocityIterations, positionIterations);
    player.Update(camera.DistanceToPlayer());
    tmxManager.update(camera);
}

void GameManager::DisplayUI(float deltaTime)
{
    score = (int)(camera.getOrigin().y / 10);
    fps = std::min(MAX_FPS, (int)(1 / deltaTime));
    std::string gameInfo = "fallSpeed : " + std::to_string(camera.FallSpeed());
    uiManager.Draw(window, camera.getView(), cameraZoom, score, fps, gameInfo);
}

void GameManager::Draw(float deltaTime)
{
    player.Animate(deltaTime);
    window->draw(tmxManager);
    window->draw(player.getSprite());
    DisplayUI(deltaTime);
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


void GameManager::UpdateCamera(float deltaTime)
{
    camera.update(deltaTime, player.getPosition().y, isRunning());
}

sf::View GameManager::getCameraView() const
{
    return camera.getView();
}


float GameManager::getMapWidth() const
{
    return tmxManager.getMapWidth();
}

float GameManager::getMapHeight() const
{
    return tmxManager.getMapHeight();
}