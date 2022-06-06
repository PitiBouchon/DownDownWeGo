#include "myTilemap.h"
#include "../rigidbody.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <unordered_set>

// Each line correspond to a line of the tileset
const std::unordered_set<int> COLLISION_TILES = {
    81, 84, 85, 86, 88, 89, 90, 92, 93, 94, 96, 97, 98,
    101, 102, 104, 109, 111, 113, 115, 117, 119, 121, 123,
    126, 127, 129, 131, 132, 134, 135, 136, 138, 139, 140, 142, 143, 144, 146, 147, 148,
    156, 157,
    184, 185, 187, 188,
    204, 205, 206, 209, 210, 212, 213
};

MyTilemap::MyTilemap(const tmx::Map &map, b2World *world, sf::Vector2f offset) {
    auto map_size = map.getTileCount();
    auto tile_size = map.getTileSize();

    for (int index = 0; index < map.getLayers().size(); index++) {
        auto const &layer = map.getLayers()[index];
        // Tile images
        if (layer->getType() == tmx::Layer::Type::Tile)
        {
            const auto &tile_layer = layer->getLayerAs<tmx::TileLayer>();
            auto map_layer = std::make_unique<MapLayer>(map, index);
            map_layer->addOffset(offset);
            tile_layers.push_back(std::move(map_layer));
            int counter = 0;
            for (auto tile : tile_layer.getTiles())
            {
                auto x = counter % map_size.x;
                auto y = counter / map_size.x;

                if (COLLISION_TILES.contains(tile.ID - 1))
                {
                    b2PolygonShape shape;
                    shape.SetAsBox(((float) tile_size.x / 2.0f) / PHYSICS_GRAPHICS_SCALE, ((float) tile_size.y / 2.0f)  / PHYSICS_GRAPHICS_SCALE);
                    auto pos = sf::Vector2f(x * tile_size.x - tile_size.x / 2.0f, y * tile_size.y - tile_size.y / 2.0f);
                    Rigidbody rb = Rigidbody(world, b2_kinematicBody, &shape, pos + offset);
                }
                counter++;
            }
        }
        /* Collision
        else if (layer->getType() == tmx::Layer::Type::Object)
        {
            const auto &object_group = layer->getLayerAs<tmx::ObjectGroup>();
            for (const auto &object : object_group.getObjects())
            {
                if (object.getShape() == tmx::Object::Shape::Ellipse && object.getAABB().width == object.getAABB().height)
                {
                    b2CircleShape shape;
                    shape.m_radius = object.getAABB().width / 2 / PHYSICS_GRAPHICS_SCALE;
                    sf::Vector2f pos = {object.getAABB().left, object.getAABB().top};
                    Rigidbody rb = Rigidbody(world, b2_kinematicBody, &shape, pos);
                }
                else if (object.getShape() == tmx::Object::Shape::Rectangle)
                {
                    b2PolygonShape shape;
                    shape.SetAsBox(object.getAABB().width / 2 / PHYSICS_GRAPHICS_SCALE, object.getAABB().height / 2 / PHYSICS_GRAPHICS_SCALE);
                    sf::Vector2f pos = {object.getAABB().left + object.getAABB().width / 2.66f, object.getAABB().top + object.getAABB().height / 2.8f};
                    Rigidbody rb = Rigidbody(world, b2_kinematicBody, &shape, pos);
                }
                else if (object.getShape() == tmx::Object::Shape::Polygon)
                {
                    int len = object.getPoints().size();
                    b2Vec2 points[len];
                    b2PolygonShape shape;
                    int p_index = 0;
                    for (auto p : object.getPoints())
                    {
                        points[p_index] = b2Vec2(p.x / PHYSICS_GRAPHICS_SCALE, p.y / PHYSICS_GRAPHICS_SCALE);
                        p_index++;
                    }
                    shape.Set(points, len);
                    sf::Vector2f pos = sf::Vector2f(object.getAABB().left - 16, object.getAABB().top - 16);
                    Rigidbody rb = Rigidbody(world, b2_kinematicBody, &shape, pos);
                }
                else
                {
                    printf("Can't handle non circle nor rectangle collision shape cuz it's boring\n");
                    exit(1);
                }
            }
        }
         */
    }
}

void MyTilemap::addOffset(sf::Vector2f offset)
{
    for (auto & tile_layer : tile_layers)
    {
        tile_layer->addOffset(offset);
    }
}

sf::FloatRect MyTilemap::getBounds() const {
    if (tile_layers.size() == 0)
    {
        printf("ERROR SOMEWHERE !");
        return sf::FloatRect(0, 0, 0, 0);
    }

    return tile_layers[0]->getBounds();
}

void MyTilemap::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    for(const auto &tile_layer : tile_layers)
    {
        rt.draw(*tile_layer, states);
    }
}

