#pragma once
#include "AGameObject.h"

class FPSCounter : public AGameObject
{
public:
	FPSCounter();
	~FPSCounter();
	void initialize() override;
	void processInput(sf::Event) override;
	void update(sf::Time deltaTime, sf::RenderWindow* window) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	sf::Time updateTime;
	sf::Text* statsText;

	void updateFPS(sf::Time elapsedTime);
};

