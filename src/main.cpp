#include <SFML/Graphics.hpp>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    sf::CircleShape circle(800, 600);
    circle.setFillColor(sf::Color(100, 250, 50));

    while (window.isOpen())
    {
	    sf::Event event{};
	    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
