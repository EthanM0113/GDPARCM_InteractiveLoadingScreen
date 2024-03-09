#pragma once
#include <iostream>
#include <thread>

// Thread class structure from other languages. By NeilDG
class IETThread
{
public:
	IETThread();
	~IETThread();

	void start(); // schedules thread execution
	static void sleep(int ms);

protected:
	virtual void run() = 0;

};

