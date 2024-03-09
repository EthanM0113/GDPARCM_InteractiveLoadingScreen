#include "StreamAssetLoader.h"

#include "IExecutionEvent.h"
#include "StringUtils.h"
#include "TextureManager.h"

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->executionEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	//std::cout << "Destroyed stream asset loader. " << std::endl;
}

void StreamAssetLoader::onStartTask()
{
	//simulate loading of very large file
	IETThread::sleep(1000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);
	//std::cout << "Loaded streaming texture:" << assetName << std::endl;
	this->executionEvent->onFinishedExecutionEvent();
	//delete this;
}

/*
void StreamAssetLoader::run()
{
	//simulate loading of very large file
	IETThread::sleep(2000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);
	std::cout << "Loaded streaming texture:" << assetName << std::endl;
	this->executionEvent->onFinishedExecutionEvent();
	delete this;
}
*/