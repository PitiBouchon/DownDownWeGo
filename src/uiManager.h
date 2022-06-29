#pragma once
#include <SFML/Graphics.hpp>

class UIManager {
private:
	const bool debug = false;
	float screenXCenter = 0;
	float screenYTop = 0;

	//UI Text
	sf::Text uiText;
	sf::Font uiFont;

	const int uiFontSize = 24;
	const sf::Color uiColor = sf::Color::White;
	std::string uiFontPath = "resources/fonts/adventures.ttf";

	//Debug Text
	sf::Text debugText;
	sf::Font debugFont;

	const int debugFontSize = 20;
	const sf::Color debugColor = sf::Color::Red;
	std::string debugFontPath = "resources/fonts/arial.ttf";

public:
	UIManager();

	void Pause(sf::RenderWindow* window, const sf::View& cameraView, const float zoom);
	void Draw(sf::RenderWindow* window, const sf::View& cameraView, const float zoom, const int score, const int fps, const std::string& gameInfo);
	void GameOver(sf::RenderWindow* window, const sf::View& cameraView, const float zoom, const int score);
};