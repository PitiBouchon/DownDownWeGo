#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <iostream>
#include "player.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DownDownWeGo");

    //Background
    Texture bgTexture;
    bgTexture.loadFromFile("./resources/cave_bg.png");
    Sprite background(bgTexture);

    //Player
    Player player("./resources/Dude_Monster_Idle_4.png", 20, 10000, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

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
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        
        window.draw(background);

        player.Move(event.key);
        player.UpdatePosition(deltaTime);
        window.draw(player.getSprite());
        
        window.display();
    }

    return 0;
}
