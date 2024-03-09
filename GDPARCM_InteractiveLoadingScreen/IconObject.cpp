#include "IconObject.h"

#include <iostream>

#include "TextureManager.h"

IconObject::IconObject(String name, int textureIndex) : AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	// assign texture
	sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(textureIndex);
	sprite->setTexture(*texture);
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime, sf::RenderWindow* window)
{
}
