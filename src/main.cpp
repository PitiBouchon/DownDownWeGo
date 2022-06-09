#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fmt/core.h>
#include <tmxlite/Map.hpp>
#include "Tile/SFMLOrthogonalLayer.h"
#include "gameManager.h"
#include "player.h"
#include "camera.h"
#include "myContactListener.h"
#include "Tile/myTilemap.h"
#include "Tile/tilemapManager.h"


// ----- GLOBAL PARAMETERS ----- //
constexpr auto MAX_FPS = 60;
constexpr auto ZOOM = 1.5f;
const auto debug = true;

// ------ Used Namespaces ----- //
using namespace std;
using namespace sf;


int main()
{
    // ----- Game Manager ----- //
    GameManager gameManager(1.0f/MAX_FPS);


    // ----- Window & Camera ----- //
    auto windowWidth = ZOOM * gameManager.getMapWidth();
    auto windowHeight = 2 * ZOOM * gameManager.getMapHeight();

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Down Down We Go", sf::Style::Close);
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);
    
    Camera camera(&window, ZOOM);
    sf::View view = camera.getView();
    window.setView(view);

    float screenYTop;
    float screenXCenter;


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


    // ----- Clock ----- //
    Clock clock;
    float time = clock.getElapsedTime().asSeconds();
    float oldtime;
    float deltaTime;


    // ----- Main Window Loop ----- //
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
                    gameManager.HandleInput(event);
                    break;

                default:
                    break;
            }
        }

        gameManager.Step();

        // ----- Window Update ----- //
        window.clear();
        camera.update(gameManager.PlayerYPos(), deltaTime);
        window.setView(camera.getView());


        // ----- Game Update ----- //
        gameManager.Update(deltaTime, camera);
        gameManager.Draw(&window);


        // ----- UI Display ----- //
        view = camera.getView();
        view.zoom(ZOOM);
        window.setView(view);

        screenYTop = window.getView().getCenter().y - windowHeight / 2;
        screenXCenter = window.getView().getCenter().x;

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

            debugText.setString("y : " + std::to_string(gameManager.PlayerYPos()));
            debugText.setPosition(0, screenYTop + debugText.getCharacterSize());
            window.draw(debugText);
        }


        // ----- Window Display ----- //
        window.display();
    }

    return 0;
}
