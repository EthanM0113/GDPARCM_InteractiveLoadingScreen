#include "ThreadPool.h"

ThreadPool::ThreadPool(String name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;

	// Create inactive workers
	for (int i = 0; i < numWorkers; i++)
	{
		PoolWorkerThread* poolWorkerThread = new PoolWorkerThread(i, this);
		inactiveThreads.push(poolWorkerThread);
	}
}

ThreadPool::~ThreadPool()
{
	stopScheduler();
	activeThreads.clear();
	while(!inactiveThreads.empty())
	{
		inactiveThreads.pop();
	}
}

void ThreadPool::startScheduler()
{
	running = true;
	start();
}

void ThreadPool::stopScheduler()
{
	running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	if(running)
	{
		pendingActions.push(action);
	}
}

void ThreadPool::setNumWorkers(int num)
{
	this->numWorkers = num;
}

void ThreadPool::run()
{
	while(running)
	{
		// There is a pending action
		if(!pendingActions.empty())
		{
			// There is an available worker
			if(!inactiveThreads.empty())
			{
				// Assign action to worker
				PoolWorkerThread* workerThread = inactiveThreads.front();
				inactiveThreads.pop();
				activeThreads[workerThread->getWorkerID()] = workerThread;

				workerThread->assignTask(pendingActions.front());
				workerThread->start();
				pendingActions.pop();
			}
		}
	}
}

void ThreadPool::onFinished(int threadID)
{
	if(activeThreads[threadID] != nullptr)
	{
		delete activeThreads[threadID];
		activeThreads.erase(threadID);

		// push replacement worker to inactive pool
		PoolWorkerThread* poolWorkerThread = new PoolWorkerThread(threadID, this);
		inactiveThreads.push(poolWorkerThread);
	}
}
