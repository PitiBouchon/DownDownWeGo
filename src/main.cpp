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

// ----- GLOBAL PARAMETERS ----- //
constexpr auto WINDOW_WIDTH = 720;
constexpr auto WINDOW_HEIGHT = 720;
constexpr auto MAX_FPS = 60;

constexpr auto GRAVITY = 100;

const auto displayFPS = true;

// ------ Used Namespaces ----- //
using namespace std;
using namespace sf;


int main()
{
    // ----- Physics ----- //
    b2Vec2 gravity(0.0f, GRAVITY); // Define the gravity vector.
    b2World world(gravity); // Construct a world object, which will hold and simulate the rigid bodies.

    MyContactListener listener;
    world.SetContactListener(&listener);

    TilemapManager tilemapManager("C:/Users/clemence/Documents/Travail/TSP/CSC4526_Cpp/Projet/DownDownWeGo/resources/maps/", &world);


    // ----- Map ----- //
    tmx::Map map;
    map.load("C:/Users/clemence/Documents/Travail/TSP/CSC4526_Cpp/Projet/DownDownWeGo/resources/maps/map1.tmx");


    // ----- Window & Camera ----- //
    RenderWindow window(VideoMode(map.getBounds().width, map.getBounds().height), "Down Down We Go");
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
    framerate.setCharacterSize(18);
    framerate.setFillColor(Color::Red);


    // ----- Background ----- //
    Texture bgTexture;
    bgTexture.loadFromFile("resources/cave_bg.png");
    Sprite background(bgTexture);
    background.setScale(WINDOW_WIDTH / background.getLocalBounds().width, WINDOW_HEIGHT / background.getLocalBounds().height);

    // ----- Player ----- //
    Player player(WINDOW_WIDTH/2, 1, &world, "resources/player_spritesheet.png");


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
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                    player.HandleInput(event);
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

        player.Update();
        player.Animate(deltaTime);
        tilemapManager.update(camera);
        
        window.draw(background);
        window.draw(tilemapManager);
        window.draw(player.getSprite());

        // Framerate display
        if (displayFPS)
        {
            fps = std::min((float)MAX_FPS, 1 / deltaTime);
            framerate.setString("fps: " + fmt::format("{:.2f}", fps));
            window.draw(framerate);
            window.display();
        }
    }

    return 0;
}
