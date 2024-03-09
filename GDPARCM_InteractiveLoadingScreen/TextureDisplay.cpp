#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "IETThread.h"

TextureDisplay::TextureDisplay() : AGameObject("TextureDisplay")
{
	unsigned int numberOfThreads = std::thread::hardware_concurrency();
	std::cout << "Number of Threads: " << numberOfThreads << std::endl;
}

void TextureDisplay::initialize()
{
}

void TextureDisplay::processInput(sf::Event event)
{
}

void TextureDisplay::update(sf::Time deltaTime, sf::RenderWindow* window)
{
	ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();

 	if(ticks > STREAMING_LOAD_DELAY && streamingType == SINGLE_STREAM)
	{
		ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(iconNumber, this);
		iconNumber++;
	}
	else if (ticks > STREAMING_LOAD_DELAY && streamingType == BATCH_LOAD && !startedStreaming)
	{
		startedStreaming = true;
		ticks = 0.0f;
		TextureManager::getInstance()->loadStreamingAssets(this);
	}
}

void TextureDisplay::onFinishedExecutionEvent()
{
	spawnObject(); // After thread prepares textures, spawns object
}

void TextureDisplay::spawnObject()
{
	String objectName = "Icon_" + to_string(iconList.size());
	IconObject* iconObj = new IconObject(objectName, iconList.size());
	iconList.push_back(iconObj);

	// Set Position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = columnGrid * IMG_WIDTH;
	float y = rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);

	//std::cout << "Icon position set at " << x << " " << y << std::endl;

	columnGrid++;
	if(columnGrid == MAX_COLUMN)
	{
		columnGrid = 0;
		rowGrid++;
	}

	GameObjectManager::getInstance()->addObject(iconObj);
}
