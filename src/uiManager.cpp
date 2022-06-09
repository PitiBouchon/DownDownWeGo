#include "uiManager.h"
#include <iostream>

UIManager::UIManager()
{
	uiFont.loadFromFile(uiFontPath);
	uiText.setFont(uiFont);
	uiText.setCharacterSize(uiFontSize);
	uiText.setFillColor(uiColor);

	debugFont.loadFromFile(debugFontPath);
	uiText.setFont(debugFont);
	uiText.setCharacterSize(debugFontSize);
	uiText.setFillColor(debugColor);
}

void UIManager::SetWindow(const sf::RenderWindow* window)
{
    screenXCenter = window->getView().getCenter().x;
    screenYTop = window->getView().getCenter().y - window->getSize().y / 2.0f;
}


void UIManager::Draw(sf::RenderWindow * window, const sf::View& cameraView, const float zoom, const int score, const int fps, const std::string& gameInfo)
{
    // ----- UI Display ----- //
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
