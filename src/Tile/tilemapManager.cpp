#include "tilemapManager.h"
#include <random>
#include <string>

/// <summary>Selects a random map among the ones corresponding to the current zone</summary>
int TilemapManager::randomMap(int currentZone)
{
    int minValue = indexZones[currentZone];
    int maxValue = (currentZone == zones - 1) ? paths.size() - 1 : indexZones[currentZone + 1] - 1;

    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution<> distribution(minValue, maxValue);
    return distribution(engine);
}

TilemapManager::TilemapManager(const std::string & maps_path, b2World *world) : world(world)
{
    for (const auto & entry : std::filesystem::directory_iterator(maps_path))
    {
        std::string path = entry.path().string();
        paths.push_back(path);
    }

    for (int i = 0; i < displayedMaps.size(); i++)
    {
        std::string path = i < 2 ? paths[i] : paths[randomMap(1)];
        tmx::Map map;

        map.load(path);
        
        sf::Vector2f offset(0, 0);
        if (i != 0) offset = sf::Vector2f(0, displayedMaps[i-1].getBounds().top + displayedMaps[i-1].getBounds().height); 

        displayedMaps[i] = MyTilemap(map, world, offset);
    }
}

void TilemapManager::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    for (const auto& map : displayedMaps)
    {
        map.draw(rt, states);
    }
}

void TilemapManager::update(const Camera &camera, int zone, float delta_time)
{
    auto *mt = &displayedMaps[indexMapToChange];

    while (mt->getBounds().top + mt->getBounds().height < camera.getPosition().y - camera.getSize().y)
    {
        std::string path = paths[randomMap(zone)];
        tmx::Map map;
        
        std::streambuf* orig_buf = std::cout.rdbuf();
        std::cout.rdbuf(nullptr); //Removes logs
        map.load(path);
        std::cout.rdbuf(orig_buf); //Restores logs

        sf::Vector2f offset;
        if (indexMapToChange == 0)
        {
            offset = sf::Vector2f(0, displayedMaps[displayedMaps.size()-1].getBounds().top + displayedMaps[displayedMaps.size()-1].getBounds().height);
        }
        else
        {
            offset = sf::Vector2f(0, displayedMaps[indexMapToChange-1].getBounds().top + displayedMaps[indexMapToChange-1].getBounds().height);
        }
        *mt = MyTilemap(map, world, offset);

        indexMapToChange++;
        indexMapToChange %= displayedMaps.size();
        mt = &displayedMaps[indexMapToChange];
    }

    for (auto &tilemap : displayedMaps) {
        tilemap.update(delta_time);
    }
}

float TilemapManager::getMapWidth() const
{
    return displayedMaps[0].getBounds().width;
}

float TilemapManager::getMapHeight() const
{
    return displayedMaps[0].getBounds().height;
}