#pragma once
#include "AGameObject.h"

class LoadingBar : public AGameObject
{
public:
	LoadingBar(String name, String spriteSheetName);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);

private:
	String spriteSheetName;
};
