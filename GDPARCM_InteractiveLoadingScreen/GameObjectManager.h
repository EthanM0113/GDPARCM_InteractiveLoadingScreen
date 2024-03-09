#pragma once
#include <string>
#include <unordered_map>
#include "AGameObject.h"


typedef std::unordered_map<std::string, AGameObject*> HashTable;
typedef std::vector<AGameObject*> List;

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	AGameObject* findObjectByName(AGameObject::String name);
	List getAllObjects();
	int activeObjects();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void addObject(AGameObject* gameObject);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(AGameObject::String name);

private:
	GameObjectManager() {};
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	HashTable gameObjectMap;
	List gameObjectList;
};

