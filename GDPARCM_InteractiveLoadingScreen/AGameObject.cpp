#include "AGameObject.h"

#include <charconv>

#include "TextureManager.h"

AGameObject::AGameObject(String name)
{
	this->name = name;
}

AGameObject::~AGameObject()
{
	delete sprite;
	delete texture;
}

AGameObject::String AGameObject::getName()
{
	return name;
}

void AGameObject::draw(sf::RenderWindow* targetWindow)
{
	if(sprite != NULL && isEnabled)
	{
		sprite->setPosition(posX, posY);
		sprite->setScale(scaleX, scaleY);
		targetWindow->draw(*sprite);
	}
}

//must be immediately called after registering to game obj manager or parent game obj
void AGameObject::setPosition(float x, float y)
{
	posX = x;
	posY = y;

	if(sprite!= nullptr)
	{
		sprite->setPosition(posX, posY);
	}
}

void AGameObject::setScale(float x, float y)
{
	scaleX = x;
	scaleY = y;

	if (sprite != nullptr)
	{
		sprite->setScale(scaleX, scaleY);
	}
}

void AGameObject::setTextureRect(int left, int top, int width, int height)
{
	if (sprite != nullptr)
	{
		sprite->setTextureRect(sf::IntRect(left, top, width, height));
	}
}

void AGameObject::setTextureFromTextureMap(String textureName, int frameIndex)
{
	sf::Texture* arrowTex = TextureManager::getInstance()->getFromTextureMap(textureName, frameIndex); // Lit
	sprite->setTexture(*arrowTex);
}

void AGameObject::setTexture(sf::Texture* texture)
{
	sprite->setTexture(*texture);
}

void AGameObject::setSmoothing(bool flag)
{
	if(texture != nullptr)
	{
		texture->setSmooth(flag);
;	}
}

void AGameObject::setEnabled(bool flag)
{
	isEnabled = flag;
}

void AGameObject::setColor(float r, float g, float b, float a)
{
	sprite->setColor(sf::Color(r, g, b, a));
}

sf::Vector2f AGameObject::getPosition()
{
	return sprite->getPosition();
}

sf::Vector2f AGameObject::getScale()
{
	return sprite->getScale();
}

sf::FloatRect AGameObject::getGlobalBounds()
{
	return sprite->getGlobalBounds();
}

bool AGameObject::getIsTextureLoaded()
{
	if (texture == nullptr)
		return false;

	return true;
}

sf::FloatRect AGameObject::getLocalBounds()
{
	return sprite->getLocalBounds();
}







