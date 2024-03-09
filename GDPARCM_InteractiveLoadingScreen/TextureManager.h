#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <string>

#include "IETSemaphore.h"
#include "ThreadPool.h"

class IExecutionEvent;
class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;

	static TextureManager* getInstance();
	void loadFromAssetList(); // pre-load assets on start
	void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); // load single stream asset according to index
	void loadSingleGIFFrame(int index, IExecutionEvent* executionEvent); // load single stream asset according to index
	void loadStreamingAssets(IExecutionEvent* executionEvent);
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	sf::Texture* getGIFTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;
	void instantiateAsTexture(String path, String assetName, bool isStreaming);
	void instantiateAsGIFTexture(String path, String assetName);
	IETSemaphore* getMutex();


private:
	TextureManager();
	TextureManager(TextureManager const&) {};
	TextureManager& operator=(TextureManager const&) {};
	static TextureManager* sharedInstance;

	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;
	TextureList gifTextureList;

	const std::string STREAMING_PATH = "Media/Streaming/";
	const std::string GIF_PATH = "Media/victor/";
	int streamingAssetCount = 0;

	void countStreamingAssets();

	ThreadPool* threadPool;

	IETSemaphore* mutex;
};

