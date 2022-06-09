#pragma once
#include <SFML/Graphics.hpp>

class UIManager {
private:
	const bool debug = true;
	const float screenXCenter;
	const float screenYTop;

	//UI Text
	sf::Text uiText;
	sf::Font uiFont;

	const int uiFontSize = 24;
	const sf::Color uiColor = sf::Color::White;
	std::string uiFontPath = "resources/adventures.ttf";


	//Debug Text
	sf::Text debugText;
	sf::Font debugFont;

	const int debugFontSize = 20;
	const sf::Color debugColor = sf::Color::Red;
	std::string debugFontPath = "resources/arial.ttf";

public:
	explicit UIManager(const sf::RenderWindow* window);
	void display(sf::RenderWindow* window, const sf::View& cameraView, const float zoom, const int score, const int fps, const std::string& gameInfo);
};