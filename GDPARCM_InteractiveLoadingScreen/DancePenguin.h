#pragma once
#include "AGameObject.h"

class DancePenguin : public AGameObject
{
public:
	DancePenguin(String name, String spriteSheetName);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);

	int* getTopRect();
	int* getLeftRect();
	int* getRightRect();
	int* getBotRect();

private:
	String spriteSheetName;
	inline static int width = 479;
	inline static int height = 466;

	inline static int topRect[4] = {0, 0, width, height};
	inline static int leftRect[4] = { width * 3, 0, width, height };
	inline static int rightRect[4] = { width, 0, width, height };
	inline static int botRect[4] = { 0, height * 8, width, height };


};
