#pragma once
#include "AGameObject.h"

class SSArrow : public AGameObject
{
public:
	SSArrow(String name, String spriteSheetName);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);

	sf::Texture* getUnlitTex();
	sf::Texture* getLitTex();
private:
	String spriteSheetName;
	sf::Texture* unlitTex;
	sf::Texture* litTex;
};

