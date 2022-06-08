#include "myTilemap.h"
#include "../rigidbody.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <unordered_set>

MyTilemap::MyTilemap(const tmx::Map &map, b2World *world, sf::Vector2f offset) {

    for (int index = 0; index < map.getLayers().size(); index++) {
        
        auto const &layer = map.getLayers()[index];
        
        // Tile images
        if (layer->getType() == tmx::Layer::Type::Tile)
        {
            const auto &tile_layer = layer->getLayerAs<tmx::TileLayer>();
            auto map_layer = std::make_unique<MapLayer>(map, index);
            
            map_layer->addOffset(offset);
            tile_layers.push_back(std::move(map_layer));
            
            if (tile_layer.getName() == "Collision")
            {
                int counter = 0;

                for (auto tile : tile_layer.getTiles())
                {
                    if (tile.ID != 0)
                    {
                        auto x = counter % map.getTileCount().x;
                        auto y = counter / map.getTileCount().x;

                        tmx::Vector2u tileSize = map.getTileSize();
                        auto boxSizeFactor = 2.0f * PHYSICS_GRAPHICS_SCALE;

                        b2PolygonShape shape;
                        shape.SetAsBox((float)tileSize.x / boxSizeFactor, (float)tileSize.y / boxSizeFactor);

                        auto pos = sf::Vector2f(tileSize.x * (x - 0.5f), tileSize.y * (y - 0.5f));
                        auto rb = Rigidbody(world, b2_kinematicBody, &shape, pos + offset);
                    }
                    counter++;
                }
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

