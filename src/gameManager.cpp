#include "gameManager.h"
#include "myContactListener.h"

//const std::string absolutePath = "C:/Users/clemence/Documents/Travail/TSP/CSC4526_Cpp/Projet/DownDownWeGo/";

GameManager::GameManager(float cameraZoom, int maxFps) :
    timeStep(1.0f/maxFps),
    world(b2Vec2(0.0f, GRAVITY)),
    tmxManager("resources/maps/", &world),
    player(tmxManager.getMapWidth() / 4, tmxManager.getMapHeight() / 2, &world, "resources/sprites/player_spritesheet.png"),
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


void GameManager::Pause(sf::Music* music)
{
    paused = !paused;
    if (paused) music->pause();
    else music->play();
}

bool GameManager::isRunning() const
{
    return !player.isDead() && !paused;
}

int GameManager::GetZone()
{
    return score * 0 + 1;
}

void GameManager::Update(float deltaTime)
{
    if (isRunning())
    {
        score = camera.getOrigin().y / 10;
        zone = GetZone();

        world.Step(timeStep, velocityIterations, positionIterations);
        player.Update(camera.DistanceToPlayer());
        tmxManager.update(camera, zone, deltaTime);
    }
}

void GameManager::DisplayUI(float deltaTime)
{
    fps = std::min(MAX_FPS, (int)(1 / deltaTime));
    std::string gameInfo = "fallSpeed : " + std::to_string(camera.FallSpeed());
    uiManager.Draw(window, camera.getView(), cameraZoom, score, fps, gameInfo);
}

void GameManager::DisplayGameOver()
{
    uiManager.GameOver(window, camera.getView(), cameraZoom, score);
}

void GameManager::Draw(float deltaTime)
{
    player.Animate(deltaTime);
    window->draw(tmxManager);
    window->draw(player.getSprite());

    if (!player.isDead()) DisplayUI(deltaTime);
    else DisplayGameOver();
}

void GameManager::HandleInput(sf::Event event)
{
    if (isRunning()) player.HandleInput(event);
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