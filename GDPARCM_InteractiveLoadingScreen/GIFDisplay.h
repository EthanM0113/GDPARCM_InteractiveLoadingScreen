#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include "SimonSaysManager.h"
#include "SFML/Audio.hpp"

class GIFFrame;

// Displays icons of textures
class GIFDisplay : public AGameObject, public IExecutionEvent
{
public:
	GIFDisplay();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);
	void draw(sf::RenderWindow* targetWindow) override;

	void onFinishedExecutionEvent() override;

	void setSSManager(SimonSaysManager* ssManager);

private:
	typedef std::vector<GIFFrame*> FrameList;
	FrameList frameList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 3.f; // Interval between icon spawning
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int frameNumber = 0;
	int maxFrames = 509; // total number of gif frames

	// Fade To Black
	sf::RectangleShape fadeToBlack;
	bool isFadeDone = false;
	sf::Time fadeInterval = sf::seconds(0.03333333333);
	uint8_t fadeAlphaIncrement = 1;
	uint8_t currentAlpha = 0;
	int fadeAlphaIncrementI = 1;
	int currentAlphaI = 0;
	int maxAlphaI = 255;

	// For GIF Playing
	sf::Clock gifClock;
	sf::Time elapsed;
	sf::Time frameDelay = sf::seconds(0.03333333333); // For 30 FPS GIF
	int playedGIFIndex = 0;
	bool firstFrame = true;
	sf::Music victorGIFAudio;

	void addFrameToList(); // add frame to vector of frames

	void playGIF(sf::Time deltaTime); // play gif

	void playfadeToBlack();

	// Loading Screen
	SimonSaysManager* ssManager;
};

