#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <iostream>
#include <fmt/core.h>
#include <tmxlite/Map.hpp>
#include "Tile/SFMLOrthogonalLayer.h"
#include "player.h"
#include "camera.h"
#include "myContactListener.h"
#include "Tile/myTilemap.h"
#include "Tile/tilemapManager.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define MAX_FPS 60

using namespace std;
using namespace sf;

int main()
{

    tmx::Map map;
    map.load("/mnt/c/Users/Pierre/Documents/TSP/2A/DevCpp/DownDownWeGo/resources/maps/map1.tmx");

    // ----- Physics ----- //
    // Define the gravity vector.
    // TODO : Valeur codée à la main
    b2Vec2 gravity(0.0f, 100.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    MyContactListener listener;
    world.SetContactListener(&listener);

    TilemapManager tilemapManager("/mnt/c/Users/Pierre/Documents/TSP/2A/DevCpp/DownDownWeGo/resources/maps/", &world);

    // ----- Window ----- //
    RenderWindow window(VideoMode(map.getBounds().width, map.getBounds().height), "DownDownWeGo");
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);
    Camera camera(&window);
    window.setView(camera.getView());
    camera.view.setSize(map.getBounds().width, map.getBounds().height);
    camera.view.setCenter(map.getBounds().width / 2 , map.getBounds().height / 2);

    // ----- Text ----- //
    sf::Font arial;
    arial.loadFromFile("resources/arial.ttf");
    
    double fps;
    Text framerate;
    framerate.setFont(arial);
    framerate.setFillColor(Color::Red);

    // ----- Background ----- //
    Texture bgTexture;
    bgTexture.loadFromFile("./resources/cave_bg.png");
    Sprite background(bgTexture);
    background.setScale(WINDOW_WIDTH / background.getLocalBounds().width, WINDOW_HEIGHT / background.getLocalBounds().height);

//    Texture blockTexture;
//    blockTexture.loadFromFile("./resources/block.png");
//    Sprite block(blockTexture);
//    block.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
//    Rigidbody rb(&world, b2_kinematicBody, block);

    // ----- Player ----- //
    Player player("./resources/player_spritesheet.png", 17, WINDOW_WIDTH / 2 - 40, 0, &world);

    // ----- Clock ----- //
    Clock clock;
    float time = clock.getElapsedTime().asSeconds();
    float oldtime;
    float deltaTime;

    // Prepare for simulation. Typically we use a time step of 60Hz and 10 iterations. 
    // This provides a high quality simulation in most game scenarios.
    float timeStep = 1.0f / MAX_FPS;
    int32 velocityIterations = 10;
    int32 positionIterations = 10;

    while (window.isOpen())
    {
        // ----- Clock Management ----- //
        oldtime = time;
        time = clock.getElapsedTime().asSeconds();
        deltaTime = time - oldtime;


        // ----- Event Management ----- //
	    sf::Event event{};
	    while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
//                case sf::Event::Resized:
//                    std::cout << "New size : " << window.getSize().x << ";" << window.getSize().x << std::endl;
//                    if (window.getSize().x % 16 != 0)
//                    {
//                        window.setSize(Vector2u(16 * (int) (window.getSize().x / 16), 16 * (int) (window.getSize().y / 16)));
//                    }
//                    camera.view.setSize(map.getBounds().width, map.getBounds().height);
//                    camera.view.setCenter(map.getBounds().width / 2 , map.getBounds().height / 2);
                    break;
                case sf::Event::KeyPressed: case sf::Event::KeyReleased:
                    player.UpdateState(event);
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                    {
                        player.Jump();
                    }
                    break;
                default:
                    break;
            }
        }

        world.Step(timeStep, velocityIterations, positionIterations);
        sf::Time duration = clock.getElapsedTime();

        // ----- Window Update ----- //
        window.clear();
        window.setView(camera.getView());
        camera.moveTo(sf::Vector2f(camera.getPosition().x, player.getSprite().getPosition().y + 60));
//        window.draw(background);

        // Player update
        player.UpdateSpeed();
        player.Animate(deltaTime);
//        block.setPosition(rb.getPixelPos());

        tilemapManager.update(camera);
        window.draw(tilemapManager);

//        window.draw(block);

        window.draw(player.getSprite());

        // Framerate display
        fps = std::min((float) MAX_FPS, 1/deltaTime);
        framerate.setString("fps: " + fmt::format("{:.0f}", fps));
        window.draw(framerate);
        window.display();
    }

    return 0;
}
