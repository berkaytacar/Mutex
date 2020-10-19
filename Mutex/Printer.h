#ifndef __Printer__
#define __Printer__

#include <mutex>
#include "rt.h"

// Solution with Monitor
//ActiveClasses can't modify the mutex through lock/unlock 
class Printer {
private:
	CMutex* m1;
public:
	void printOnScreen(int x, int y, int thread) {
		m1->Wait();
		MOVE_CURSOR(x, y);             	// move cursor to cords [x,y] = 5,5
		printf("Thread %d", thread);
		fflush(stdout);		      	// force output to be written to screen now
		m1->Signal();
	}

	Printer(string Name) {
		m1 = new CMutex(string("__Mutex__") + string(Name));
	}

};

#endif