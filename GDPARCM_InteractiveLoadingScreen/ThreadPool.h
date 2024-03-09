#pragma once
#include <queue>
#include <unordered_map>
#include "IETThread.h"
#include "PoolWorkerThread.h"


class IWorkerAction;

class IFinishedTask
{
public:
	virtual void onFinished(int threadID) = 0;
};

// Thread class that can handles/schedules N worker threads that can be reused.
class ThreadPool : public IETThread, public IFinishedTask
{
private:
	typedef std::string String;
	typedef std::queue<PoolWorkerThread*> ThreadList;
	typedef std::unordered_map<int, PoolWorkerThread*> ActiveThreadMap;
	typedef std::queue<IWorkerAction*> ActionList;

public:
	ThreadPool(String name, int numWorkers);
	~ThreadPool();

	void startScheduler();
	void stopScheduler();
	void scheduleTask(IWorkerAction* action);

	void setNumWorkers(int num);

private:
	void run() override;
	void onFinished(int threadID) override;

	String name;
	bool running = false;
	int numWorkers = 0;
	ActiveThreadMap activeThreads;
	ThreadList inactiveThreads;
	ActionList pendingActions;
};

