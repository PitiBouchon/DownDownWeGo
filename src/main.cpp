#include <SFML/Graphics.hpp>
#include <iostream>
#include <format>
#include "player.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

using namespace std;
using namespace sf;

int main()
{
    //Window
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DownDownWeGo");
    window.setFramerateLimit(60);

    //Text
    sf::Font arial;
    arial.loadFromFile("resources/arial.ttf");
    
    double fps;
    Text framerate;
    framerate.setFont(arial);
    framerate.setFillColor(Color::Red);

    //Background
    Texture bgTexture;
    bgTexture.loadFromFile("./resources/cave_bg.png");
    Sprite background(bgTexture);

    //Player
    Player player("./resources/Dude_Monster_Idle_4.png", 20, 500, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    //Clock
    Clock clock;
    double time = clock.getElapsedTime().asSeconds();
    double oldtime;
    double deltaTime;

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
