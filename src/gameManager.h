#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fmt/core.h>
#include <tmxlite/Map.hpp>
#include "Tile/SFMLOrthogonalLayer.h"
#include "player.h"
#include "Tile/myTilemap.h"
#include "Tile/tilemapManager.h"
#include "myContactListener.h"

class GameManager {
private:
	//Physics parameters
	const float GRAVITY = 100;
	const int32 velocityIterations = 10;
	const int32 positionIterations = 10;
	float timeStep;

	b2World world;
	MyContactListener listener;
	TilemapManager tmxManager;
	Player player;

public:
	explicit GameManager(float timeStep);

	void Step();
	void Update(float deltaTime, const Camera& camera);
	void Draw(sf::RenderWindow* window);
	void HandleInput(sf::Event event);

	float getMapWidth() const;
	float getMapHeight() const;

	float PlayerYPos() const;
	float PlayerYSpeed() const;
};