#include "BGObject.h"
#include <iostream>

#include "BaseRunner.h"
#include "TextureManager.h"

BGObject::BGObject(String name) : AGameObject(name)
{
}

void BGObject::initialize()
{
	std::cout << "Named as " << this->getName() << "\n";

	// assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
	texture->setRepeated(true);
	sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	//make bg height x k to emulate repeating bg
	this->sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT * 8));
	this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
}

void BGObject::processInput(sf::Event)
{
}

void BGObject::update(sf::Time deltaTime, sf::RenderWindow* window)
{
	// make BG scroll
	sf::Vector2f position = getPosition();
	position.y += SPEED_MULTIPLIER * deltaTime.asSeconds();
	setPosition(position.x, position.y);

	sf::Vector2f localPos = sprite->getPosition();
	if(localPos.y * deltaTime.asSeconds() > 0)
	{
		// reset bg position
		setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
	}
	else
	{
		
	}
}
