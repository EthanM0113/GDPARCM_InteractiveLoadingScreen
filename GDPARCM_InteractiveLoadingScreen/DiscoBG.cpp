#include "DiscoBG.h"

#include "TextureManager.h"

DiscoBG::DiscoBG(String name, String spriteSheetName) : AGameObject(name)
{
	this->spriteSheetName = name;

	// assign texture
	sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(spriteSheetName, 0);
	sprite->setTexture(*texture);
}

void DiscoBG::initialize()
{
}

void DiscoBG::processInput(sf::Event event)
{
}

void DiscoBG::update(sf::Time deltaTime, sf::RenderWindow* window)
{
}
