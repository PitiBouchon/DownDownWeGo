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
constexpr auto ZOOM = 2;
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

    TilemapManager tilemapManager("resources/maps/", &world);


    // ----- Map ----- //
    tmx::Map map;
    map.load("resources/maps/map1.tmx");

    // ----- Window & Camera ----- //
    RenderWindow window(VideoMode(2* map.getBounds().width, 2* map.getBounds().height), "Down Down We Go", sf::Style::Close);
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);
    
    Camera camera(&window);
    camera.view.setSize(sf::Vector2f(window.getSize()));
    camera.view.setCenter(sf::Vector2f(window.getSize().x / 4, window.getSize().y / 2));
    camera.view.zoom(1.0f/ZOOM);

    sf::View view = camera.getView();
    window.setView(view);

    // ----- Text ----- //
    sf::Font arial;
    arial.loadFromFile("resources/arial.ttf");
    
    int fps = 0;
    Text framerate;
    framerate.setFont(arial);
    framerate.setCharacterSize(18);
    framerate.setFillColor(Color::Red);

    sf::Font UIFont;
    UIFont.loadFromFile("resources/adventures.ttf");

    int depth = 0;
    Text depthText;
    depthText.setFont(UIFont);
    depthText.setCharacterSize(24);
    depthText.setFillColor(Color::White);

    // ----- Player ----- //
    Player player(window.getSize().x / 2, 1, &world, "resources/player_spritesheet.png");

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

        depth = (int) (camera.getOrigin().y / 10);
        depthText.setString(std::to_string(depth) + " M");
        depthText.setPosition(camera.getCenter().x, window.getView().getCenter().y - window.getSize().y /2 + 20);
        window.draw(depthText);

        // FPS display
        if (displayFPS)
        {
            fps = std::min(MAX_FPS,(int) (1 / deltaTime));
            framerate.setString("fps: " + std::to_string(fps));
            framerate.setPosition(0, window.getView().getCenter().y - window.getSize().y / 2);
            window.draw(framerate);
        }

        window.display();
    }

    return 0;
}
