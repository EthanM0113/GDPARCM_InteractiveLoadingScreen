#pragma once
#include "IETThread.h"
#include "IWorkerAction.h"

class IExecutionEvent;
class GIFFrameLoader : public IWorkerAction
{
private:
	typedef std::string String;

public:
	GIFFrameLoader(String path, IExecutionEvent* executionEvent);
	~GIFFrameLoader();
	void onStartTask() override;


private:
	String path;
	IExecutionEvent* executionEvent;
};

