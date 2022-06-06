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

class MyTilemap : public sf::Drawable {
private:
    std::vector<std::unique_ptr<MapLayer>> tile_layers;
public:
    MyTilemap() = default;
    MyTilemap(const tmx::Map& map, b2World *world, sf::Vector2f offset);
    void addOffset(sf::Vector2f offset);
    sf::FloatRect getBounds() const;
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;
};


#endif //DOWNDOWNWEGO_MYTILEMAP_H
