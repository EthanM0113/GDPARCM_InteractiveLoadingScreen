#pragma once
#include <SFML/Window/Event.hpp>

#include "AGameObject.h"

class BGObject : public AGameObject
{
public:
	BGObject(std::string name);
	void initialize();
	void processInput(sf::Event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);
private:
	const float SPEED_MULTIPLIER = 200.f;
};

