#pragma once
#include <mutex>

// Representation of busy waiting semaphore
class BusyWaitSemaphore
{
public:
	BusyWaitSemaphore(int available, int limit);
	BusyWaitSemaphore(int limit); // available = limit
	~BusyWaitSemaphore();

	void acquire();
	void release();

private:
	typedef std::mutex Mutex;
	Mutex* guard;
	int permits = 0;
	int maxPermits = 0;

	void wait() const; // sleeps thread and awakens when available permits are acquirable
};

