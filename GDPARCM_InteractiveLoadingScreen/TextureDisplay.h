#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"

class IconObject;

// Displays icons of textures
class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);

	void onFinishedExecutionEvent() override;

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	enum StreamingType {BATCH_LOAD = 0, SINGLE_STREAM = 1};
	const float STREAMING_LOAD_DELAY = 3.f; // Interval between icon spawning
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0;

	int iconNumber = 0;
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	void spawnObject();
};

