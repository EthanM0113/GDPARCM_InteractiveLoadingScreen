#include "BaseRunner.h"

#include <iostream>

#include "BGObject.h"
#include "DiscoBG.h"
#include "FPSCounter.h"
#include "GameObjectManager.h"
#include "GIFDisplay.h"
#include "SimonSaysManager.h"
#include "TextureDisplay.h"
#include "TextureManager.h"

const float FRAME_RATE = 60.0f;
BaseRunner* BaseRunner::sharedInstance = NULL;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {
	window.setFramerateLimit(int(FRAME_RATE));

	// Load Initial Textures
	TextureManager::getInstance()->loadFromAssetList();
	//TextureManager::getInstance()->loadStreamingAssets();

	// Load Objects
	/*
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);
	*/

	/*
	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);
	*/

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	// For Interactive Loading Screen
	DiscoBG* discoBGObject = new DiscoBG("DiscoBG", "discobg");
	discoBGObject->setScale(1.5, 1.4);
	discoBGObject->setColor(255, 255, 255, 100);
	//discoBGObject->setPosition(0, 10);
	GameObjectManager::getInstance()->addObject(discoBGObject);

	SimonSaysManager* ssManager = new SimonSaysManager();
	GameObjectManager::getInstance()->addObject(ssManager);

	// Loads and displays Victor frames
	GIFDisplay* gifDisplay = new GIFDisplay();
	GameObjectManager::getInstance()->addObject(gifDisplay);
	gifDisplay->setSSManager(ssManager);
}

BaseRunner* BaseRunner::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new BaseRunner();
	}
	return sharedInstance;
}

void BaseRunner::run()
{
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	while(window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(deltaTime));
		render();

		previousTime = currentTime;
	}
}

float BaseRunner::getFPS()
{
	return fps;
}

void BaseRunner::render()
{
	window.clear();
	GameObjectManager::getInstance()->draw(&window);
	window.display();
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if(window.pollEvent(event))
	{
		switch (event.type)
		{
			default: GameObjectManager::getInstance()->processInput(event); break;
			case sf::Event::Closed:
				window.close();
				break;
		}
	}


}

void BaseRunner::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime, &window);
}
