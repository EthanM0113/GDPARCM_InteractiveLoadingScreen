#include "FPSCounter.h"

#include <iostream>

#include "BaseRunner.h"

FPSCounter::FPSCounter() : AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete statsText->getFont();
	delete statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{

	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	statsText = new sf::Text();
	statsText->setFont(*font);
	statsText->setPosition(BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70);
	statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	statsText->setOutlineThickness(2.5f);
	statsText->setCharacterSize(35);
}

void FPSCounter::processInput(sf::Event)
{
}

void FPSCounter::update(sf::Time deltaTime, sf::RenderWindow* window)
{
	updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if(statsText != nullptr)
	{
		targetWindow->draw(*statsText);
	}
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	updateTime += elapsedTime;
	if (updateTime >= sf::seconds(0.5f))
	{
		updateTime = sf::seconds(0.0f);
		statsText->setString("FPS: " + std::to_string(BaseRunner::getInstance()->getFPS()) + "\n");
	}

}
