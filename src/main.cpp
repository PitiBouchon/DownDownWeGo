#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <iostream>
#include <format>
#include "player.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

using namespace std;
using namespace sf;

int main()
{
    // ----- Window ----- //
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DownDownWeGo");
    window.setFramerateLimit(60);

    //Text
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


    // ----- Physics ----- //

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);


    // ----- Player ----- //
    Player player("./resources/Dude_Monster_Idle_4.png", 20, 500, WINDOW_WIDTH / 2, 0, &world);


    // ----- Clock ----- //
    Clock clock;
    double time = clock.getElapsedTime().asSeconds();
    double oldtime;
    double deltaTime;

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    while (window.isOpen())
    {
        oldtime = time;
        time = clock.getElapsedTime().asSeconds();
        deltaTime = time - oldtime;

	    sf::Event event{};
	    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear();
        
        window.draw(background);

        player.Move(event.key);
        player.UpdatePosition(deltaTime);
        window.draw(player.getSprite());
        
        //Framerate display
        fps = std::min(60.0, 1/deltaTime);
        framerate.setString("fps: " + format("{:.2f}", fps));
        window.draw(framerate);

        window.display();
    }

    return 0;
}
