#include "PoolWorkerThread.h"

#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int ID, IFinishedTask* finishedTask)
{
	threadID = ID;
	this->finishedTask = finishedTask;
}

PoolWorkerThread::~PoolWorkerThread()
{
}

int PoolWorkerThread::getWorkerID()
{
	return threadID;
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->assignedTask = action;
}

void PoolWorkerThread::run()
{
	assignedTask->onStartTask();
	finishedTask->onFinished(threadID);
}
