#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fmt/core.h>
#include "gameManager.h"
#include <WinUser.h>


// ----- GLOBAL PARAMETERS ----- //
constexpr auto MAX_FPS = 60;
constexpr auto ZOOM = 1.5f;


// ------ Used Namespaces ----- //
using namespace std;
using namespace sf;


int main()
{
    ShowWindow(GetConsoleWindow(), SW_SHOW);

    // ----- Game Manager ----- //
    GameManager gameManager(ZOOM, MAX_FPS);
    auto windowSize = sf::Vector2u(ZOOM * gameManager.getMapWidth(), 2 * ZOOM * gameManager.getMapHeight());


    // ----- Window Creation ----- //
    RenderWindow window(VideoMode(windowSize.x, windowSize.y), "Down Down We Go", sf::Style::Close);
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);
    window.setSize(windowSize);

    sf::View view = gameManager.getCameraView();
    window.setView(view);

    gameManager.SetWindow(&window);


    // ----- Music ----- //
    sf::Music BGM;
    if (!BGM.openFromFile("resources/music/trippin-ost.wav")) return -1;
    BGM.setLoop(true);

    float volume = 100;
    BGM.setVolume(volume);
    BGM.play();


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
        

        // ----- Window Update ----- //
        window.clear();
        gameManager.UpdateCamera(deltaTime);
        window.setView(gameManager.getCameraView());


        // ----- Event Management ----- //
	    sf::Event event;
	    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) gameManager.Pause(&BGM);
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) gameManager.HandleInput(event);
        }


        // ----- Game Update ----- //
        gameManager.Update();
        gameManager.Draw(deltaTime);
        window.display();
    }

    return 0;
}
