#include "SSArrow.h"

#include "TextureManager.h"

SSArrow::SSArrow(String name, String spriteSheetName) : AGameObject(name)
{
	this->spriteSheetName = spriteSheetName;
}

void SSArrow::initialize()
{
	// assign texture
	sprite = new sf::Sprite();
	std::cout << "Number of Frames in " << spriteSheetName << ": " << TextureManager::getInstance()->getNumFrames(spriteSheetName) << std::endl;
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(spriteSheetName, 0);
	sprite->setTexture(*texture);

	unlitTex = texture;

	sf::Texture* lit = TextureManager::getInstance()->getFromTextureMap(spriteSheetName, 1);
	litTex = lit;
}

void SSArrow::processInput(sf::Event event)
{
}

void SSArrow::update(sf::Time deltaTime, sf::RenderWindow* window)
{
}

sf::Texture* SSArrow::getUnlitTex()
{
	return unlitTex;
}

sf::Texture* SSArrow::getLitTex()
{
	return litTex;
}




