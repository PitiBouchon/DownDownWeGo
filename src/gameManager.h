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
	
	sf::RenderWindow* window = nullptr;
	Camera camera;
	UIManager uiManager;

	float cameraZoom;
	const int MAX_FPS;
	int fps = 0;

	bool isPaused = false;
	int score = 0;

public:
	GameManager(float cameraZoom, int maxFps);
	void SetWindow(sf::RenderWindow* window_p);

	void Update();
	void DisplayUI(float deltaTime);
	void Draw(float deltaTime);
	void HandleInput(sf::Event event);

	void Pause();
	void Resume();
	bool isRunning() const;

	void UpdateCamera(float deltaTime);
	sf::View getCameraView() const;

	float getMapWidth() const;
	float getMapHeight() const;
};