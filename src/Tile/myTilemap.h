#ifndef DOWNDOWNWEGO_MYTILEMAP_H
#define DOWNDOWNWEGO_MYTILEMAP_H

#include "SFMLOrthogonalLayer.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <limits>
#include <iostream>
#include <cmath>
#include "../destructible.h"

/// Used as a wrapper for MapLayer (defined in SFMLOrthogonalLayer.h) and adding physics
/// for each tile of the layer named Collisionusing box2d
class MyTilemap : public sf::Drawable {
private:
    std::vector<std::unique_ptr<MapLayer>> tile_layers;
    std::vector<Destructible> destructibles;
public:
    MyTilemap() = default;
    MyTilemap(const tmx::Map& map, b2World *world, sf::Vector2f offset);

    /// Offset is used to place a tilemap at a location
    void addOffset(sf::Vector2f offset) const;
    sf::FloatRect getBounds() const;
    void update(float delta_time);

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;
};


#endif //DOWNDOWNWEGO_MYTILEMAP_H
