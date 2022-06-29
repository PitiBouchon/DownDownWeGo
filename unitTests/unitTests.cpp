#include <gtest/gtest.h>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "../src/Tile/myTilemap.h"
#include "../src/Tile/tilemapManager.h"
#include "../src/player.h"
#include "../src/gameManager.h"

const std::string absolutePath = "C:/Users/clemence/Documents/Travail/TSP/CSC4526_Cpp/Projet/DownDownWeGo/";


TEST(TestTilemap, TestCreate)
{
    tmx::Map map;
    bool loaded = map.load(absolutePath + "/resources/maps/map1.tmx");
    ASSERT_EQ(loaded, true);

    b2World world(b2Vec2(0, 10));

    ASSERT_NO_THROW(MyTilemap(map, &world, sf::Vector2f(0, 0)));
}

TEST(TestTilemapManager, TestMapSize)
{
    b2World world(b2Vec2(0, 10));

    TilemapManager tilemapManager(absolutePath + "/resources/maps/", &world);

    EXPECT_EQ(tilemapManager.getMapWidth(), 320);
    EXPECT_EQ(tilemapManager.getMapHeight(), 256);
}


TEST(TestPlayerState, PlayerCreate)
{
    b2World world(b2Vec2(0, 10));
    GameManager gameManager(1, 60);
    Player player(0, 0, &world, absolutePath + "/resources/sprites/player_spritesheet.png", gameManager);

    ASSERT_TRUE(States::IDLE, player.getState());
}

TEST(TestPlayerState, PlayerJump)
{
    b2World world(b2Vec2(0, 10));
    GameManager gameManager(1, 60);
    Player player(0, 0, &world, absolutePath + "/resources/sprites/player_spritesheet.png", gameManager);
    
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Space;
    
    player.HandleInput(event);

    ASSERT_TRUE(States::JUMP, player.getState());
}