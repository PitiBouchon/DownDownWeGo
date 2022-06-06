#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <iostream>
#include <fmt/core.h>
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.h"
#include "player.h"
#include "camera.h"
#include "myContactListener.h"

constexpr auto WINDOW_WIDTH = 720;
constexpr auto WINDOW_HEIGHT = 720;
constexpr auto MAX_FPS = 60;

const auto displayFPS = true;

using namespace std;
using namespace sf;

int main()
{
    // ----- Window & Camera ----- //
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DownDownWeGo");
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);

    Camera camera(&window);


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


    // ----- Physics ----- //
    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    MyContactListener listener;
    world.SetContactListener(&listener);

    Texture blockTexture;
    blockTexture.loadFromFile("./resources/block.png");
    Sprite block(blockTexture);
    block.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    Rigidbody rb(&world, b2_kinematicBody, block);


    // ----- Player ----- //
    Player player(WINDOW_WIDTH/2, 0, 5, &world, "./resources/player_spritesheet.png");


    Texture blockTexture2;
    blockTexture2.loadFromFile("./resources/block.png");
    Sprite block2(blockTexture2);
    block2.setPosition(WINDOW_WIDTH / 2 + 25, WINDOW_HEIGHT / 2 - 200);
    Rigidbody rb2(&world, b2_dynamicBody, block2);


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
                    
                    //For debug purposes
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
                    {
                        camera.move(sf::Vector2f(0, -20));
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                    {
                        camera.move(sf::Vector2f(0, 20));
                    }
                    break;
                default:
                    break;
            }
        }

        world.Step(timeStep, velocityIterations, positionIterations);


        // ----- Window Update ----- //
        window.clear();
        window.setView(camera.getView());
        window.draw(background);

        // Player update
        player.Update();
        player.Animate(deltaTime);
        window.draw(player.getSprite());
        
        //Blocks
        block.setPosition(rb.getPixelPos());
        window.draw(block);
        block2.setPosition(rb2.getPixelPos());
        window.draw(block2);

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
