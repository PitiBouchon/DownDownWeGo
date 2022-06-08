#ifndef DOWNDOWNWEGO_TILEMAPMANAGER_H
#define DOWNDOWNWEGO_TILEMAPMANAGER_H

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "myTilemap.h"
#include "../camera.h"
#include <filesystem>

class TilemapManager : public sf::Drawable {
private:
    std::array<MyTilemap, 5> displayed_maps;
    int index_map_to_change = 0;
    std::vector<std::string> paths;
    b2World *world;

    float mapHeight;
    float mapWidth;

public:
    TilemapManager(const std::string& maps_path, b2World *world);
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;
    void update(const Camera &camera);

    float getMapWidth() const;
    float getMapHeight() const;
};


#endif //DOWNDOWNWEGO_TILEMAPMANAGER_H
