#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class AGameObject: sf::NonCopyable
{
public:
	typedef std::string String;
	AGameObject(String name);
	~AGameObject();
	virtual void initialize() = 0;
	virtual void processInput(sf::Event event) = 0;
	virtual void update(sf::Time deltaTime, sf::RenderWindow* window) = 0;
	virtual void draw(sf::RenderWindow* targetWindow);
	String getName();

	virtual void setPosition(float x, float y);
	virtual void setScale(float x, float y);
	virtual void setTextureRect(int left, int top, int width, int height);
	virtual void setTextureFromTextureMap(String textureName, int frameIndex);
	virtual void setTexture(sf::Texture* texture);
	virtual void setSmoothing(bool flag);
	virtual void setEnabled(bool flag);
	virtual void setColor(float r, float g, float b, float a);
	virtual sf::FloatRect getLocalBounds();
	virtual sf::FloatRect getGlobalBounds();
	virtual bool getIsTextureLoaded();
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getScale();

protected:
	String name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	bool isEnabled = true;

	float posX = 0.0f; float posY = 0.0f;
	float scaleX = 1.0f; float scaleY = 1.0f;
};

