#include "tilemapManager.h"
#include <string>

TilemapManager::TilemapManager(const std::string & maps_path, b2World *world) : world(world)
{
    for (const auto & entry : std::filesystem::directory_iterator(maps_path))
    {
        std::string path = entry.path().string();
        paths.push_back(path);
    }

    for (int i = 0; i < displayed_map.size(); i++)
    {
        std::string path = paths[rand() % paths.size()];
        tmx::Map map;
        
        std::streambuf* orig_buf = std::cout.rdbuf();
        std::cout.rdbuf(nullptr); //Removes Logs

        map.load(path);
        
        std::cout.rdbuf(orig_buf); //Restores Logs


        if (i != 0)
        {
            auto offset = sf::Vector2f(0, displayed_map[i-1].getBounds().top + displayed_map[i-1].getBounds().height);
            displayed_map[i] = MyTilemap(map, world, offset);
        }
        else
        {
            displayed_map[i] = MyTilemap(map, world, sf::Vector2f(0, 0));
        }
    }
}

void TilemapManager::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    for (const auto& map : displayed_map)
    {
        map.draw(rt, states);
    }
}

void TilemapManager::update(const Camera &camera)
{
    auto *mt = &displayed_map[index_map_to_change];

    if (mt->getBounds().top + mt->getBounds().height < camera.getPosition().y - camera.getSize().y)
    {
        std::string path = paths[rand() % paths.size()];
        tmx::Map map;
        
        std::streambuf* orig_buf = std::cout.rdbuf();
        std::cout.rdbuf(nullptr);
        map.load(path);
        std::cout.rdbuf(orig_buf);

        sf::Vector2f offset;
        if (index_map_to_change == 0)
        {
            offset = sf::Vector2f(0, displayed_map[displayed_map.size()-1].getBounds().top + displayed_map[displayed_map.size()-1].getBounds().height);
        }
        else
        {
            offset = sf::Vector2f(0, displayed_map[index_map_to_change-1].getBounds().top + displayed_map[index_map_to_change-1].getBounds().height);
        }
        *mt = MyTilemap(map, world, offset);

        index_map_to_change++;
        index_map_to_change %= displayed_map.size();
    }
}