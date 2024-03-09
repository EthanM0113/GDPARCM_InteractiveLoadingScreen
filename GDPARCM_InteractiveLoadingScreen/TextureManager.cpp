#include "TextureManager.h"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "GIFFrameLoader.h"
#include "IETThread.h"
#include "StreamAssetLoader.h"
#include "StringUtils.h"


TextureManager* TextureManager::sharedInstance = NULL;

TextureManager::TextureManager()
{
	countStreamingAssets();

	// Instantiate Thread Pool
	int numberOfThreads = std::thread::hardware_concurrency();
	std::cout << "Number of Threads: " << numberOfThreads << std::endl;

	threadPool = new ThreadPool("Thread Pool", numberOfThreads);
	threadPool->startScheduler();

	// Instantiate mutex
	mutex = new IETSemaphore(1);
	mutex->release(1); // release 1st permit
}

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for(const auto& entry: std::filesystem::directory_iterator(STREAMING_PATH))
	{
		streamingAssetCount++;
	}
	std::cout << "Total Streaming Assets " << streamingAssetCount << std::endl;

}

void TextureManager::instantiateAsTexture(String path, String assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);

	if(assetName == "arrowLit")
		textureMap["arrowUnlit"].push_back(texture); // Utilizing texture map to store both arrow textures
	else
		textureMap[assetName].push_back(texture);

	if(isStreaming)
	{
		streamTextureList.push_back(texture);
	}
	else
	{
		baseTextureList.push_back(texture);
	}
}

void TextureManager::instantiateAsGIFTexture(String path, String assetName)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);

	gifTextureList.push_back(texture);
}

IETSemaphore* TextureManager::getMutex()
{
	return mutex;
}

TextureManager* TextureManager::getInstance()
{
	if(sharedInstance == NULL)
	{
		sharedInstance = new TextureManager();
	}
	return sharedInstance;
}

void TextureManager::loadFromAssetList()
{
	std::cout << "Reading from Asset List" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while(std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		instantiateAsTexture(path, assetName, false);
		std::cout << "Loaded Texture: " << assetName << std::endl;
	}

}

void TextureManager::loadStreamingAssets(IExecutionEvent* executionEvent)
{
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
	{
		/*
		// Simulate loading of very big asset/s
		IETThread::sleep(200);

		String path = entry.path().generic_string();
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		instantiateAsTexture(path, assetName, true);
		*/

		String path = entry.path().generic_string();

		/*
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		instantiateAsTexture(path, assetName, true);
		std::cout << "Loaded streaming texture:" << assetName << std::endl;
		*/

		StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
		//assetLoader->start();
		threadPool->scheduleTask(assetLoader);


		//std::cout << "Loaded Texture: " << assetName << std::endl;
	}
}


void TextureManager::loadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
	{
		if(index == fileNum)
		{
			// Simulate loading of very big asset/s
			//IETThread::sleep(200);

			String path = entry.path().generic_string();

			/*
			std::vector<String> tokens = StringUtils::split(path, '/');
			String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
			instantiateAsTexture(path, assetName, true);
			std::cout << "Loaded streaming texture:" << assetName << std::endl;
			*/

			StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
			//assetLoader->start();
			threadPool->scheduleTask(assetLoader);
			

			break;
		}

		fileNum++;
	}

}

void TextureManager::loadSingleGIFFrame(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(GIF_PATH))
	{
		if (index == fileNum)
		{

			String path = entry.path().generic_string();

			std::cout << "Index: " << index << ", Path: " << path << std::endl;

			GIFFrameLoader* gifLoader = new GIFFrameLoader(path, executionEvent);
			
			threadPool->scheduleTask(gifLoader);

			break;
		}

		fileNum++;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if(!textureMap[assetName].empty())
	{
		return textureMap[assetName][frameIndex];
	}
	else
	{
		std::cout << "No texture found for: " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!textureMap[assetName].empty())
	{
		return textureMap[assetName].size();
	}
	else
	{
		std::cout << "No texture found for: " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getStreamTextureFromList(const int index)
{
	//std::cout << "Loaded Textures: " << getNumLoadedStreamTextures() << std::endl;
	return streamTextureList[index];
}

sf::Texture* TextureManager::getGIFTextureFromList(const int index)
{
	return gifTextureList[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return streamTextureList.size();
}
