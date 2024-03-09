#include "DancePenguin.h"

#include "TextureManager.h"

DancePenguin::DancePenguin(String name, String spriteSheetName) : AGameObject(name)
{
	this->spriteSheetName = spriteSheetName;
}

void DancePenguin::initialize()
{
	// assign texture
	sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(spriteSheetName, 0);
	sprite->setTexture(*texture);
}

void DancePenguin::processInput(sf::Event event)
{
}

void DancePenguin::update(sf::Time deltaTime, sf::RenderWindow* window)
{
}

int* DancePenguin::getTopRect()
{
	return topRect;
}

int* DancePenguin::getLeftRect()
{
	return leftRect;
}

int* DancePenguin::getRightRect()
{
	return rightRect;
}

int* DancePenguin::getBotRect()
{
	return botRect;
}
