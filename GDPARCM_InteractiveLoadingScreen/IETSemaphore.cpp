#include "IETSemaphore.h"

IETSemaphore::IETSemaphore(int available)
{
	semaphore = new Semaphore(available); // in class would be, (0, available) I think

}

IETSemaphore::~IETSemaphore()
{
	delete semaphore;
}

void IETSemaphore::acquire() const
{
	semaphore->acquire();
}

void IETSemaphore::acquire(int permits) const
{
	for(int i = 0; i < permits; i++)
	{
		semaphore->acquire();
	}
}

void IETSemaphore::release() const
{
	semaphore->release();
}

void IETSemaphore::release(int permits) const
{
	semaphore->release(permits);
}
