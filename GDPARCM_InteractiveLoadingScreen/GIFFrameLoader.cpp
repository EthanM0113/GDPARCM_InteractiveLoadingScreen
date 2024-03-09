#include "GIFFrameLoader.h"

#include "IExecutionEvent.h"
#include "StringUtils.h"
#include "TextureManager.h"

GIFFrameLoader::GIFFrameLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->executionEvent = executionEvent;
}

GIFFrameLoader::~GIFFrameLoader()
{
	//std::cout << "Destroyed stream asset loader. " << std::endl;
}

void GIFFrameLoader::onStartTask()
{
	TextureManager::getInstance()->getMutex()->acquire();
	//simulate loading of very large file
	IETThread::sleep(500);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsGIFTexture(path, assetName);

	this->executionEvent->onFinishedExecutionEvent();
}

