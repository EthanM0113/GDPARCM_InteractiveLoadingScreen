#pragma once
// Listens for finished threads after specific functions. 
class IExecutionEvent
{
public:
	virtual void onFinishedExecutionEvent() = 0;
};

