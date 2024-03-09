#pragma once

#include "AGameObject.h"
#include "DanceBanana.h"
#include "DancePenguin.h"
#include "LoadingBar.h"
#include "SSArrow.h"
#include "vector"
#include "SFML/Audio.hpp"

using namespace std;

class SimonSaysManager : public AGameObject
{
public:
	SimonSaysManager();
	~SimonSaysManager();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime, sf::RenderWindow* window) override;
	void draw(sf::RenderWindow* targetWindow) override;

	void setFrameListSize(int size); // From GIF Dispaly
	void stopCruiseBGM(); // For GIF Display
	void playHitSFX(int sfxIndex); // 1,2,3,4
	void playGoodComboSFX(int comboCount); // 5 and 10
private:
	int min = 1;
	int max = 4;
	int range;
	vector<int> numberHistory;
	bool isPlayerTurn = false; // Generate number first
	bool didDisplayWaitOnce = false;
	int index = 0;
	int combo = 0;
	vector<SSArrow*> arrowList; // 0 - left, 1 - down, 2 - up, 3 - right
	bool setupFinished = false;
	bool lightArrow = false;
	int displayArrowIndex = 0;
	bool isPrintingHistory = false;
	sf::Time elapsed;
	bool isDoneWaiting = false;
	bool clearLightsFirst = false;
	int printIndex = 0;
	string spriteSheetName = "arrowUnlit";
	sf::Clock delayClock;
	sf::Time delayInterval = sf::seconds(0.5f);

	DancePenguin* penguin;

	LoadingBar* loadingBar;
	float moveDistance = 220.f; // "Speed" of loading bar
	float lbXSpawn = -2010.0f;
	float lbYSpawn = -150.0f;
	float currentX = 0;
	int frameListSize = 0;
	float loadingSmoothener = 0.017014f;

	DanceBanana* danceBanana;
	int* tempRect; // for banana
	float bXSpawn = -50.f;
	float bYSpawn = -23.f;
	float currentBananaX = 0;
	float bananaMoveDistance = 220.f; // "Speed" of banana
	int currentBananaFrame = 0;
	sf::Clock bananaClock;
	sf::Time bananaFrameInterval = sf::seconds(0.1f);

	// Combo Variables
	sf::Text* comboValueText;
	sf::SoundBuffer goodComboSFX1;
	sf::SoundBuffer goodComboSFX2;
	sf::Sound comboSfxPlayer;

	// Loading Screen BG Music
	sf::Music cruiseBGM;

	// SFX
	sf::SoundBuffer hitSFX1;
	sf::SoundBuffer hitSFX2;
	sf::SoundBuffer hitSFX3;
	sf::SoundBuffer hitSFX4;
	sf::Sound sfxPlayer;

	// For debugging
	bool printOnce = true;

	// Utility
	bool setupVariables = false;
	sf::RenderWindow* rWindow;
	void addNewNumber();
	void printNumberHistory();
	void restart();
	void spawnArrows();
	void spawnPenguin();
	void setArrowLight(int index, bool flag);
	void turnOffAllLights();
	void setPenguinState(int state); // 0 - idle, 1 - left, 2 - right, 3 - sit
	void updateLoadingBar();
	void setBananaState(int index); // 0 - start frame
	void updateComboText();
};

