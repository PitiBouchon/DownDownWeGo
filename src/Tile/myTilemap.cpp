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
                    auto rb = Rigidbody(world, b2_kinematicBody, &shape, pos + offset);
                }
                counter++;
            }
        }
    }
}

void MyTilemap::addOffset(sf::Vector2f offset) const
{
    for (const auto & tile_layer : tile_layers)
    {
        tile_layer->addOffset(offset);
    }
}

sf::FloatRect MyTilemap::getBounds() const {
    if (tile_layers.empty())
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

