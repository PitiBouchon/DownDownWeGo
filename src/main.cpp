#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fmt/core.h>
#include "gameManager.h"
#include "camera.h"


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

    
    // ----- Music ----- //
    /* Include Music.hpp LNK 2019 error : needs solving
    sf::Music BGM;
    if (!BGM.openFromFile("resources/trippin-ost.wav")) return -1; // error
    BGM.play();
    */

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
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) gameManager.Pause();
        }

        // ----- Window Update ----- //
        window.clear();
        camera.update(deltaTime, gameManager.PlayerYPos(), gameManager.isRunning());
        window.setView(camera.getView());


        // ----- Game Update ----- //
        if (gameManager.isRunning())
        {
            gameManager.HandleInput(event);
            gameManager.Update(camera);
        }
        gameManager.Draw(&window, deltaTime);


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

            debugText.setString("ySpeed : " + std::to_string(gameManager.PlayerYSpeed()));
            debugText.setPosition(0, screenYTop + debugText.getCharacterSize());
            window.draw(debugText);
        }


        // ----- Window Display ----- //
        window.display();
    }

    return 0;
}
