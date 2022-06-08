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
constexpr auto MAX_FPS = 60;
constexpr auto GRAVITY = 100;
constexpr auto ZOOM = 1.5f;
const auto debug = true;

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


    // ----- Map ----- //
    string absolutePath = "C:/Users/clemence/Documents/Travail/TSP/CSC4526_Cpp/Projet/DownDownWeGo/";
    TilemapManager tilemapManager(absolutePath + "resources/maps/", &world);


    // ----- Window & Camera ----- //
    auto windowWidth = ZOOM * tilemapManager.getMapWidth();
    auto windowHeight = 2 * ZOOM * tilemapManager.getMapHeight();

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Down Down We Go", sf::Style::Close);
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);
    
    Camera camera(&window);
    camera.view.setSize(sf::Vector2f(window.getSize()));
    camera.view.setCenter(sf::Vector2f(windowWidth / (2 * ZOOM), windowHeight));
    camera.view.zoom(1.0f/ZOOM);

    sf::View view = camera.getView();
    window.setView(view);

    // ----- Text ----- //
    sf::Font arial;
    arial.loadFromFile("resources/arial.ttf");
    
    int fps = 0;
    Text debugText;
    debugText.setFont(arial);
    debugText.setCharacterSize(18);
    debugText.setFillColor(Color::Red);

    sf::Font UIFont;
    UIFont.loadFromFile("resources/adventures.ttf");

    int depth = 0;
    Text depthText;
    depthText.setFont(UIFont);
    depthText.setCharacterSize(24);
    depthText.setFillColor(Color::White);

    // ----- Player ----- //
    Player player(windowWidth / 2, windowHeight / 2, &world, "resources/player_spritesheet.png");

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

        // ----- Window Update ----- //
        window.clear();
        camera.update(player.getPosition().y, deltaTime);
        window.setView(camera.getView());

        player.Update();
        player.Animate(deltaTime);
        tilemapManager.update(camera);
        
        window.draw(tilemapManager);
        window.draw(player.getSprite());

        //----- UI Display ---- //
        view = camera.getView();
        view.zoom(ZOOM);
        window.setView(view);

        auto screenYTop = window.getView().getCenter().y - windowHeight / 2;
        auto screenXCenter = window.getView().getCenter().x;

        depth = (int) (camera.getOrigin().y / 10);
        depthText.setString(std::to_string(depth) + " M");
        depthText.setPosition(screenXCenter - depthText.getLocalBounds().width /2, screenYTop + 20);
        window.draw(depthText);

        // Debug display (fps and other info)
        if (debug)
        {
            fps = std::min(MAX_FPS,(int) (1 / deltaTime));
            debugText.setString("fps: " + std::to_string(fps));
            debugText.setPosition(0, screenYTop);
            window.draw(debugText);

            debugText.setString("y speed: " + std::to_string((int)player.getVerticalSpeed()));
            debugText.setPosition(0, screenYTop + debugText.getCharacterSize());
            window.draw(debugText);
        }

        window.display();
    }

    return 0;
}
