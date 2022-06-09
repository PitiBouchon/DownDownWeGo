#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fmt/core.h>
#include <tmxlite/Map.hpp>
#include "Tile/SFMLOrthogonalLayer.h"
#include "Tile/myTilemap.h"
#include "Tile/tilemapManager.h"
#include "myContactListener.h"
#include "player.h"
#include "camera.h"
#include "uiManager.h"

class GameManager {
private:
	//Physics parameters
	const float GRAVITY = 100;
	const int32 velocityIterations = 10;
	const int32 positionIterations = 10;
	float timeStep;

	//Variables
	b2World world;
	MyContactListener listener;
	TilemapManager tmxManager;
	Player player;

	Camera camera;
	UIManager uiManager;

	float cameraZoom;
	const int MAX_FPS;
	int fps = 0;

	bool isPaused = false;
	int score = 0;

public:
	GameManager(const sf::RenderWindow* window, float cameraZoom, int maxFps);

	void Update();
	void DisplayUI(sf::RenderWindow* window, float deltaTime);
	void Draw(sf::RenderWindow* window, float deltaTime);
	void HandleInput(sf::Event event);

	void Pause();
	void Resume();
	bool isRunning() const;

	void UpdateCamera(float deltaTime);
	sf::View getCameraView() const;

	float getMapWidth() const;
	float getMapHeight() const;
};