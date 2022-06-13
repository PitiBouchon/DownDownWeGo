#include "uiManager.h"
#include <iostream>

UIManager::UIManager()
{
	uiFont.loadFromFile(uiFontPath);
	uiText.setFont(uiFont);
	uiText.setCharacterSize(uiFontSize);
	uiText.setFillColor(uiColor);

	debugFont.loadFromFile(debugFontPath);
	debugText.setFont(debugFont);
    debugText.setCharacterSize(debugFontSize);
    debugText.setFillColor(debugColor);
}


void UIManager::Draw(sf::RenderWindow * window, const sf::View& cameraView, const float zoom, const int score, const int fps, const std::string& gameInfo)
{
    screenXCenter = window->getView().getCenter().x;
    screenYTop = window->getView().getCenter().y - window->getSize().y / 2.0f;

    sf::View view = cameraView;
    view.zoom(zoom);
    window->setView(view);

    uiText.setString(std::to_string(score) + " M");
    uiText.setPosition(screenXCenter - uiText.getLocalBounds().width / 2, screenYTop + 20);
    window->draw(uiText);

    // Debug display (fps and other info)
    if (debug)
    {
        debugText.setString("fps: " + std::to_string(fps));
        debugText.setPosition(0, screenYTop);
        window->draw(debugText);

        debugText.setString(gameInfo);
        debugText.setPosition(0, screenYTop + debugText.getCharacterSize());
        window->draw(debugText);
    }
}

void UIManager::GameOver(sf::RenderWindow* window, const sf::View& cameraView, const float zoom, const int score)
{
    sf::View view = cameraView;
    view.zoom(zoom);
    window->setView(view);

    gameOverText = "Game Over\n";
    uiText.setString(gameOverText);
    uiText.setPosition(window->getView().getCenter().x - uiText.getLocalBounds().width / 2, window->getView().getCenter().y - uiText.getCharacterSize());
    window->draw(uiText);

    gameOverText = "You traveled " + std::to_string(score) + " M";
    uiText.setString(gameOverText);
    uiText.setPosition(window->getView().getCenter().x - uiText.getLocalBounds().width / 2, window->getView().getCenter().y + uiText.getCharacterSize());
    window->draw(uiText);
}