#include <gtest/gtest.h>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "../src/Tile/myTilemap.h"

TEST(TestGroupName, TestName)
{
    EXPECT_EQ(true, true);
}

TEST(TestTilemap, Test1)
{
    tmx::Map map;
    map.load("../../resources/maps/map1.tmx");

    b2World world(b2Vec2(0, 10));

    MyTilemap tilemap(map, &world, sf::Vector2f(0, 0));

    EXPECT_EQ(true, true);
}
