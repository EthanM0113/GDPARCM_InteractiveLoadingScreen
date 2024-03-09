#pragma once
#include <semaphore>

// C++ 20 Semaphore
class IETSemaphore
{
public:
	IETSemaphore(int available);
	~IETSemaphore();

	void acquire() const;
	void acquire(int permits) const;
	void release() const;
	void release(int permits) const;

private:
	const static int GLOBAL_MAX_PERMITS = 50;
	typedef std::counting_semaphore<GLOBAL_MAX_PERMITS> Semaphore; // Max permits during compile time for compiler.
																   // Good practice is to set max permits to anticipated max threads
	Semaphore* semaphore;
};


