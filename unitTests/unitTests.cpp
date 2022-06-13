#include <gtest/gtest.h>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "../src/Tile/myTilemap.h"
#include "../src/Tile/tilemapManager.h"

TEST(TestTilemap, TestCreate)
{
    tmx::Map map;
    bool loaded = map.load("../resources/maps/map1.tmx");
    ASSERT_EQ(loaded, true);

    b2World world(b2Vec2(0, 10));

    EXPECT_NO_THROW(MyTilemap(map, &world, sf::Vector2f(0, 0)));
}

TEST(TestTilemapManager, TestMapSize)
{
    b2World world(b2Vec2(0, 10));

    TilemapManager tilemapManager("../resources/maps/", &world);

    ASSERT_EQ(tilemapManager.getMapWidth(), 320);
    ASSERT_EQ(tilemapManager.getMapHeight(), 256);
}

