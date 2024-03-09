#include "DanceBanana.h"

#include "TextureManager.h"

DanceBanana::DanceBanana(String name, String spriteSheetName) : AGameObject(name)
{
	this->spriteSheetName = spriteSheetName;
}

void DanceBanana::initialize()
{
	// assign texture
	sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(spriteSheetName, 0);
	sprite->setTexture(*texture);
}

void DanceBanana::processInput(sf::Event event)
{
}

void DanceBanana::update(sf::Time deltaTime, sf::RenderWindow* window)
{
}

int* DanceBanana::getIdleRect()
{
	return idleRect;
}

int* DanceBanana::getFrameRect(int frameIndex)
{
	int tempRect[4] = { width * frameIndex, 0, width, height };
	return tempRect;
}

int DanceBanana::getMaxFrames()
{
	return maxFrames;
}
