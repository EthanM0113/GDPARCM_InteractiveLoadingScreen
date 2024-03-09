#pragma once
#include "AGameObject.h"

class DanceBanana : public AGameObject
{
public:
	DanceBanana(String name, String spriteSheetName);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);

	int* getIdleRect();
	int* getFrameRect(int frameIndex);
	int getMaxFrames();

private:
	String spriteSheetName;
	inline static int width = 470;
	inline static int height = 498;

	inline static int idleRect[4] = { 0, 0, width, height };

	int maxFrames = 8; // 8 sprites in sprite sheet
	int currentFrame = 0; // 0 for starting 

};

