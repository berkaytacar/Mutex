#ifndef __Printer__
#define __Printer__

#include <mutex>
#include "rt.h"


class Printer {
private:
	mutex* m1;
public:
	void printOnScreen(int x, int y, int thread) {
		m1->lock();
		MOVE_CURSOR(x, y);             	// move cursor to cords [x,y] = 5,5
		printf("Thread %d", thread);
		fflush(stdout);		      	// force output to be written to screen now
		m1->unlock();
	}

	Printer() {
		m1 = new mutex();
	}

};

#endif