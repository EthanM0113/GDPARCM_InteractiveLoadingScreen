#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "GIFFrame.h"
#include "GIFDisplay.h"

#include "FPSCounter.h"
#include "IETSemaphore.h"
#include "SFML/Audio.hpp"


GIFDisplay::GIFDisplay() : AGameObject("GIFDisplay")
{
	// Spawn Fade 2 Black Rectangle
	fadeToBlack.setFillColor(sf::Color{ 0, 0, 0, currentAlpha});
	fadeToBlack.setSize(sf::Vector2f(1920, 1080));
}

void GIFDisplay::initialize()
{
}

void GIFDisplay::processInput(sf::Event event)
{
}

void GIFDisplay::update(sf::Time deltaTime, sf::RenderWindow* window)
{
	if(frameNumber <= maxFrames && frameList.size() <= maxFrames)
	{
		ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();

		if (ticks > STREAMING_LOAD_DELAY && streamingType == SINGLE_STREAM)
		{
			ticks = 0.0f;
			TextureManager::getInstance()->loadSingleGIFFrame(frameNumber, this);
			frameNumber++;
		}
	}
	else if (frameNumber > maxFrames && frameList.size() > maxFrames)
	{
		if(!isFadeDone)
		{
			playfadeToBlack();
		}
		else
		{
			// Play GIF
			playGIF(deltaTime);
		}
	}

	// pass frame list size to loading bar
	ssManager->setFrameListSize(frameList.size());
}

void GIFDisplay::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);
	targetWindow->draw(fadeToBlack);
}

void GIFDisplay::onFinishedExecutionEvent()
{
	addFrameToList(); // After thread prepares textures, spawns object, CRITICAL SECTION
}

void GIFDisplay::setSSManager(SimonSaysManager* ssManager)
{
	this->ssManager = ssManager;
}

void GIFDisplay::addFrameToList()
{
	String objectName = "VictorGIF_" + to_string(frameList.size());
	GIFFrame* frameObj = new GIFFrame(objectName, frameList.size());
	frameList.push_back(frameObj);

	GameObjectManager::getInstance()->addObject(frameObj);

	// Setup Frames for Presentation
	frameObj->setScale(2.7f, 2.7f);

	frameObj->setEnabled(false); // Dont draw first, wait for all objects

	cout << "Added Frame: " << objectName << endl;

	TextureManager::getInstance()->getMutex()->release();
}

void GIFDisplay::playGIF(sf::Time deltaTime)
{
	if(playedGIFIndex < maxFrames + 1)
	{
		if (firstFrame)
		{
			cout << "FINISHED LOADING ALL FRAMES" << endl;

			firstFrame = false;
			gifClock.restart();

			frameList[playedGIFIndex]->setEnabled(true);

			// Stop BGM Track
			ssManager->stopCruiseBGM();

			// Reinstantiate FPS Counter to display above video
			GameObjectManager::getInstance()->deleteObjectByName("FPSCounter");
			FPSCounter* fpsCounter = new FPSCounter();
			GameObjectManager::getInstance()->addObject(fpsCounter);

			// Play backing track
			victorGIFAudio.openFromFile("Media/Tekken-8-Victor-Chevalier_s-Rage-Art.ogg");
			victorGIFAudio.setVolume(50);
			victorGIFAudio.play();
		}

		elapsed = gifClock.getElapsedTime();
		if (elapsed > frameDelay) // time in between frames
		{
			playedGIFIndex++;
			if (playedGIFIndex < maxFrames + 1)
			{
				frameList[playedGIFIndex]->setEnabled(true);
				gifClock.restart();
			}
		}
	}
}

void GIFDisplay::playfadeToBlack()
{
	elapsed = gifClock.getElapsedTime();
	if (elapsed > fadeInterval)
	{
		currentAlpha += fadeAlphaIncrement;
		currentAlphaI += fadeAlphaIncrementI;
		fadeToBlack.setFillColor(sf::Color{ 0, 0, 0, currentAlpha });

		if (currentAlphaI > maxAlphaI)
			isFadeDone = true;

		gifClock.restart();
	}
}
