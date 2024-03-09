#include "GIFFrame.h"

#include <iostream>

#include "TextureManager.h"

GIFFrame::GIFFrame(String name, int textureIndex) : AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void GIFFrame::initialize()
{
	// assign texture
	sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getGIFTextureFromList(textureIndex);
	sprite->setTexture(*texture);
}

void GIFFrame::processInput(sf::Event event)
{
}

void GIFFrame::update(sf::Time deltaTime, sf::RenderWindow* window)
{
}
