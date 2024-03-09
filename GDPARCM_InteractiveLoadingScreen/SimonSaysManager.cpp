#include "SimonSaysManager.h"

#include <iostream>
#include <set>

#include "DancePenguin.h"
#include "GameObjectManager.h"
#include "IETThread.h"
#include "SSArrow.h"
#include "TextureManager.h"

SimonSaysManager::SimonSaysManager() : AGameObject("SimonSaysManager")
{
	cout << "CREATED SIMON SAYS MANAGER" << endl;

	// Seed rng
	srand((unsigned)time(NULL));

	// Evaluate range
	range = (max - min) + 1;

	// Spawn Arrows
	spawnArrows();
	arrowList[0]->setScale(5, 5);

	arrowList[1]->setScale(5, 5);
	arrowList[1]->setSmoothing(true);
	arrowList[2]->setScale(5, 5);
	arrowList[2]->setSmoothing(true);
	arrowList[3]->setScale(5, 5);
	arrowList[3]->setSmoothing(true);

	arrowList[0]->setPosition(50, 450);
	arrowList[1]->setPosition(325, 750);
	arrowList[2]->setPosition(325, 150);
	arrowList[3]->setPosition(600, 450);

	// Spawn Penguin
	spawnPenguin();
	penguin->setPosition(1000, 200);
	penguin->setScale(2, 2);

	// Spawn Loading Bar
	loadingBar = new LoadingBar("LoadingBar", "loading");
	GameObjectManager::getInstance()->addObject(loadingBar);
	loadingBar->setTextureRect(6, 6, 1007, 240);
	loadingBar->setScale(2.0, 1.0);
	loadingBar->setPosition(lbXSpawn, lbYSpawn);
	currentX = lbXSpawn;

	// Spawn Dance Banana
	danceBanana = new DanceBanana("DanceBanana", "banana");
	GameObjectManager::getInstance()->addObject(danceBanana);
	danceBanana->setScale(0.23, 0.23);
	danceBanana->setPosition(bXSpawn, lbYSpawn);
	setBananaState(0);
	currentBananaFrame = 0;
	bananaClock.restart();

	// Spawn Combo Text
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/ArcadeNormal-ZDZ.ttf");

	comboValueText = new sf::Text();
	comboValueText->setFont(*font);
	comboValueText->setPosition(1290.f, 200.f);
	comboValueText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	comboValueText->setOutlineThickness(3);
	comboValueText->setCharacterSize(50);
	updateComboText();
	goodComboSFX1.loadFromFile("Media/goodCombo1.wav");
	goodComboSFX2.loadFromFile("Media/goodCombo2.wav");

	// Set SFX
	hitSFX1.loadFromFile("Media/hitSFX1.wav");
	hitSFX2.loadFromFile("Media/hitSFX2.wav");
	hitSFX3.loadFromFile("Media/hitSFX3.wav");
	hitSFX4.loadFromFile("Media/hitSFX4.wav");

	// Play Cruise BGM
	cruiseBGM.openFromFile("Media/tekkenpartycruise.ogg");
	cruiseBGM.setVolume(50);
	cruiseBGM.setLoop(true);
	cruiseBGM.play();

	
}

SimonSaysManager::~SimonSaysManager()
{
}

void SimonSaysManager::initialize()
{
}

void SimonSaysManager::processInput(sf::Event event)
{
	if(isPlayerTurn && index < numberHistory.size())
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				if (numberHistory[index] == 1)
				{
					cout << "NICE" << endl;
					index++;
				}
				else
				{
					restart();
				}
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				if (numberHistory[index] == 2)
				{
					cout << "NICE" << endl;
					index++;
				}
				else
				{
					restart();
				}
			}
			if (event.key.code == sf::Keyboard::Num3)
			{
				if (numberHistory[index] == 3)
				{
					cout << "NICE" << endl;
					index++;
				}
				else
				{
					restart();
				}
			}
			if (event.key.code == sf::Keyboard::Num4)
			{
				if (numberHistory[index] == 4)
				{
					cout << "NICE" << endl;
					index++;
				}
				else
				{
					restart();
				}
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				// Get Mouse Pos
				sf::Vector2i mouse_pos = sf::Mouse::getPosition(*rWindow); // Mouse position relative to the window
				sf::Vector2f world_pos = (*rWindow).mapPixelToCoords(mouse_pos); // Mouse position translated into world 

				if (arrowList[0]->getGlobalBounds().contains(world_pos)) {

					cout << "Clicked Left Arrow" << endl;
					setArrowLight(0, true);
					setPenguinState(1);

					// Play SFX
					playHitSFX(1);

					if (numberHistory[index] == 1)
					{
						cout << "NICE" << endl;
						index++;
					}
					else
					{
						restart();
					}
				}
				else if (arrowList[1]->getGlobalBounds().contains(world_pos)) {

					cout << "Clicked Down Arrow" << endl;
					setArrowLight(1, true);
					setPenguinState(3);

					// Play SFX
					playHitSFX(2);

					if (numberHistory[index] == 3)
					{
						cout << "NICE" << endl;
						index++;
					}
					else
					{
						restart();
					}


				}
				else if (arrowList[2]->getGlobalBounds().contains(world_pos)) {

					cout << "Clicked Up Arrow" << endl;
					setArrowLight(2, true);
					setPenguinState(0);

					// Play SFX
					playHitSFX(3);

					if (numberHistory[index] == 2)
					{
						cout << "NICE" << endl;
						index++;
					}
					else
					{
						restart();
					}
				}
				else if (arrowList[3]->getGlobalBounds().contains(world_pos)) {

					cout << "Clicked Right Arrow" << endl;
					setArrowLight(3, true);
					setPenguinState(2);

					// Play SFX
					playHitSFX(4);

					if (numberHistory[index] == 4)
					{
						cout << "NICE" << endl;
						index++;
					}
					else
					{
						restart();
					}
				}
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			turnOffAllLights();
		}
	}
}

void SimonSaysManager::update(sf::Time deltaTime, sf::RenderWindow* window)
{
	// Update Loading Bar
	updateLoadingBar();

	if (!setupVariables)
	{
		rWindow = window;
		setupVariables = true;
	}

	if(isPlayerTurn && !isPrintingHistory)
	{
		if(index < numberHistory.size())
		{
			if(!didDisplayWaitOnce)
			{
				cout << "Waiting for Player Input..." << endl;
				didDisplayWaitOnce = true;
			}
		}
		else
		{
			combo++;
			updateComboText();
			playGoodComboSFX(combo);
			isPlayerTurn = false;
			didDisplayWaitOnce = false;
			index = 0;
		}
	}
	else if(!isPlayerTurn && !isPrintingHistory)
	{
		addNewNumber();
		printNumberHistory();
	}

	if(clearLightsFirst)
	{
		turnOffAllLights();
		clearLightsFirst = false;
	}
	else if (isPrintingHistory && !clearLightsFirst)
	{
		if(printIndex < numberHistory.size())
		{
			// Delay
			elapsed = delayClock.getElapsedTime();
			if (elapsed > delayInterval)
			{
				isDoneWaiting = true;

				// Get arrow index
				if (numberHistory[printIndex] == 1)
					displayArrowIndex = 0;
				else if (numberHistory[printIndex] == 2)
					displayArrowIndex = 2;
				else if (numberHistory[printIndex] == 3)
					displayArrowIndex = 1;
				else if (numberHistory[printIndex] == 4)
					displayArrowIndex = 3;

				if (lightArrow)
				{
					cout << "Light Arrow" << endl;
					setArrowLight(displayArrowIndex, true);
					if (displayArrowIndex == 0)
					{
						setPenguinState(1);
						playHitSFX(1);
					}

					else if(displayArrowIndex == 1)
					{
						setPenguinState(3);
						playHitSFX(2);
					}
					else if (displayArrowIndex == 2)
					{
						setPenguinState(0);
						playHitSFX(3);
					}
					else if (displayArrowIndex == 3)
					{
						setPenguinState(2);
						playHitSFX(4);
					}
				}

				else
				{
					cout << "Unlight Arrow" << endl;
					setArrowLight(displayArrowIndex, false);
				}

				if (!lightArrow)
				{
					lightArrow = true;
					printIndex++;
				}
				else
				{
					lightArrow = !lightArrow;
				}

				// Reset clock
				isDoneWaiting = false;
				delayClock.restart();
			}
			else
			{
				cout << "DELAYING" << endl;
			}
		}
		else
		{
			isPrintingHistory = false;
			isPlayerTurn = true;
		}
	}


}

void SimonSaysManager::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (comboValueText != nullptr)
	{
		targetWindow->draw(*comboValueText);
	}
}

void SimonSaysManager::addNewNumber()
{
	int random = min + (rand() % max);
	numberHistory.push_back(random);
}

void SimonSaysManager::printNumberHistory()
{
	cout << "Number History: ";
	/*
	for (int i = 0; i < numberHistory.size(); i++)
	{
		/*
		// Delay
		IETThread::sleep(1000);

		cout << numberHistory[i];
		if(i != numberHistory.size() - 1)
		{
			cout << ", ";
		}
		else
		{
			cout << endl;

			// Delay
			IETThread::sleep(1000);

			// Clear Screen
			system("cls");
		}
		

		cout << numberHistory[i];

		if (numberHistory[i] == 1)
			displayArrowIndex = 0;
		else if (numberHistory[i] == 2)
			displayArrowIndex = 2;
		else if (numberHistory[i] == 3)
			displayArrowIndex = 1;
		else if (numberHistory[i] == 4)
			displayArrowIndex = 3;


		setArrowLight(displayArrowIndex, true);
		
		unlitArrow = false;
		delayClock.restart();
		while(!unlitArrow)
		{
			sf::Time elapsed = delayClock.getElapsedTime();
			cout << "Elapsed: " << elapsed.asSeconds() << endl;
			if(elapsed > delayInterval)
			{
				//Unlight arrow
				setArrowLight(displayArrowIndex, false);
				unlitArrow = true;
			}
		}

		setArrowLight(displayArrowIndex, false);
	}
	*/


	printIndex = 0;
	lightArrow = true;

	// Reset clock
	isDoneWaiting = false;
	delayClock.restart();

	clearLightsFirst = true;
	isPrintingHistory = true;
}

void SimonSaysManager::restart()
{
	cout << "WRONG" << endl;
	numberHistory.clear();

	// Exit player turn loop
	combo = 0;
	updateComboText();
	isPlayerTurn = false;
	didDisplayWaitOnce = false;
	index = numberHistory.size();
}

void SimonSaysManager::spawnArrows()
{
	for(int i = 0; i < 4; i++)
	{
		SSArrow* arrow = new SSArrow("ArrowButton", "arrowUnlit");
		GameObjectManager::getInstance()->addObject(arrow);

		arrow->setTextureRect(i * 64, 0, 64, 64);
		arrowList.push_back(arrow);
	}
}

void SimonSaysManager::spawnPenguin()
{
	penguin = new DancePenguin("DancePenguin", "penguin");
	GameObjectManager::getInstance()->addObject(penguin);

}

void SimonSaysManager::setArrowLight(int index, bool flag)
{
	if (flag)
	{
		arrowList[index]->setTexture(arrowList[index]->getLitTex());
	}
	else
	{
		arrowList[index]->setTexture(arrowList[index]->getUnlitTex());
	}
}

void SimonSaysManager::turnOffAllLights()
{
	// Turn off light
	setArrowLight(0, false);
	setArrowLight(1, false);
	setArrowLight(2, false);
	setArrowLight(3, false);
}

void SimonSaysManager::setPenguinState(int state)
{
	if(state == 0) // idle
	{
		penguin->setTextureRect(penguin->getTopRect()[0], penguin->getTopRect()[1],
			penguin->getTopRect()[2], penguin->getTopRect()[3]);
	}
	else if(state == 1) // left
	{
		penguin->setTextureRect(penguin->getLeftRect()[0], penguin->getLeftRect()[1],
			penguin->getLeftRect()[2], penguin->getLeftRect()[3]);
	}
	else if (state == 2) // right
	{
		penguin->setTextureRect(penguin->getRightRect()[0], penguin->getRightRect()[1],
			penguin->getRightRect()[2], penguin->getRightRect()[3]);
	}
	else if (state == 3) // sit
	{
		penguin->setTextureRect(penguin->getBotRect()[0], penguin->getBotRect()[1],
			penguin->getBotRect()[2], penguin->getBotRect()[3]);
	}
}

void SimonSaysManager::updateLoadingBar()
{
	loadingBar->setPosition(currentX, lbYSpawn);
	danceBanana->setPosition(currentBananaX, bYSpawn);

	// Move Loading Bar according to frameList size AND dancing banan
	currentX = lbXSpawn + (frameListSize * moveDistance * loadingSmoothener); // instead of using delta time, just using a small number for smoothening
	currentBananaX = bXSpawn + (frameListSize * bananaMoveDistance * loadingSmoothener);

	// Update Banana Sprite
	float bananaElapsed = bananaClock.getElapsedTime().asSeconds();
	if(bananaElapsed > bananaFrameInterval.asSeconds())
	{
		currentBananaFrame++;
		if (currentBananaFrame < danceBanana->getMaxFrames())
		{
			setBananaState(currentBananaFrame);
		}
		else // loop sprite
		{
			currentBananaFrame = 0;
			setBananaState(currentBananaFrame);
		}

		bananaClock.restart();
	}
	
}

void SimonSaysManager::setBananaState(int index)
{
	tempRect = danceBanana->getFrameRect(index);
	danceBanana->setTextureRect(tempRect[0], tempRect[1],tempRect[2], tempRect[3]);
}

void SimonSaysManager::updateComboText()
{
	comboValueText->setString("COMBO " + std::to_string(combo));
}

void SimonSaysManager::stopCruiseBGM()
{
	cruiseBGM.stop();
}

void SimonSaysManager::playHitSFX(int sfxIndex)
{
	if(sfxIndex == 1)
	{
		sfxPlayer.setBuffer(hitSFX1);
	}
	else if (sfxIndex == 2)
	{
		sfxPlayer.setBuffer(hitSFX2);
	}
	else if (sfxIndex == 3)
	{
		sfxPlayer.setBuffer(hitSFX3);
	}
	else if (sfxIndex == 4)
	{
		sfxPlayer.setBuffer(hitSFX4);
	}
	sfxPlayer.setVolume(50);
	sfxPlayer.play();
}

void SimonSaysManager::playGoodComboSFX(int comboCount)
{
	if (comboCount % 4 == 0)
	{
		comboSfxPlayer.setBuffer(goodComboSFX2);
		comboSfxPlayer.setVolume(50);
		comboSfxPlayer.play();
		}
	else if(comboCount % 2 == 0)
	{
		comboSfxPlayer.setBuffer(goodComboSFX1);
		comboSfxPlayer.setVolume(50);
		comboSfxPlayer.play();
	}
	
}

void SimonSaysManager::setFrameListSize(int size)
{
	this->frameListSize = size;
}
