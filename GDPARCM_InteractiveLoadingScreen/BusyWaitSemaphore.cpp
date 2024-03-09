#include "BusyWaitSemaphore.h"

#include "IETThread.h"

BusyWaitSemaphore::BusyWaitSemaphore(int available, int limit)
{
	permits = available;
	maxPermits = limit;
	guard = new Mutex();
}

BusyWaitSemaphore::BusyWaitSemaphore(int limit)
{
	maxPermits = limit;
	permits = maxPermits;
}

void BusyWaitSemaphore::acquire()
{
	guard->lock(); // lock prevents multiple thread from using acquire
	if(permits > 0)
	{
		permits--;
		guard->unlock(); // unlock reverses lock effect
	}
	else
	{
		guard->unlock();
		wait(); // wait till permit requirement is available
		guard->lock();
		permits--; // when exiting busy wait, acquire the permit now
		guard->unlock();
	}
}

void BusyWaitSemaphore::release()
{
	guard->lock();
	if (permits < maxPermits)
	{
		permits++;
	}
	guard->unlock();
}

void BusyWaitSemaphore::wait() const
{
	// busy wait in while loop
	while(permits == 0)
	{
		IETThread::sleep(1);
	}
}
