#pragma once
#include "IETThread.h"

class IWorkerAction;
class IFinishedTask;
// Worker in thread pool / job system
class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int ID, IFinishedTask* finishedTask);
	~PoolWorkerThread();
	int getWorkerID();
	void assignTask(IWorkerAction* action);

private:
	void run() override;
	IFinishedTask* finishedTask;
	int threadID;
	IWorkerAction* assignedTask;
};

