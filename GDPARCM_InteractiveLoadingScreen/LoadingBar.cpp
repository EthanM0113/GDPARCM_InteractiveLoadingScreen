#include "LoadingBar.h"

#include "TextureManager.h"

LoadingBar::LoadingBar(String name, String spriteSheetName) : AGameObject(name)
{
	this->spriteSheetName = spriteSheetName;
}

void LoadingBar::initialize()
{
	// assign texture
	sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(spriteSheetName, 0);
	sprite->setTexture(*texture);
}

void LoadingBar::processInput(sf::Event event)
{
}

void LoadingBar::update(sf::Time deltaTime, sf::RenderWindow* window)
{
}
