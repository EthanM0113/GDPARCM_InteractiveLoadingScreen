#pragma once
#include "AGameObject.h"

class GIFFrame : public AGameObject
{
public:
	GIFFrame(String name, int textureIndex);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);

private:
	int textureIndex = 0;
};
