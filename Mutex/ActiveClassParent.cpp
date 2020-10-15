#include "rt.h"
#include "ActiveClassParent.h"
//#include <atomic> //C++11 library
#include <mutex>
using namespace std;
//
//	To create an active class with its own thread running through it. Derive a new class
//	from the base class 'ActiveClass' and then you MUST override the inherited base class function int main(void)
//	if you do not override main() with your own function it will not compile since the class will be abstract
//
//	Note that all active classes are created in the SUSPENDED state to avoid races between the constructor for the class
//	and the kernel which otherwise might try to run a thread through an incompleted constructed class object
//
//	Therefore you must forcible Resume() the class to allow its thread to run.
//

int ActiveClassParent::main(void)
{

	//create the mutex m1
	//std::mutex m1;
	// create the 3 other child threads
	mutex* m1 = new mutex();

	Child1 c1(1, m1);
	Child2 c2(2, m1);
	Child3 c3(3, m1);

	// allow childs to run
	c1.Resume();
	c2.Resume();
	c3.Resume();

	for (int i = 0; i < 50000; i++) {
		//lock_guard<mutex> theLock(m1);
		m1->lock();
		MOVE_CURSOR(5, 5);             	// move cursor to cords [x,y] = 5,5
		printf("Thread 1");
		fflush(stdout);		      	// force output to be written to screen now
		m1->unlock();
	}
	
	// wait for the 3 other child threads to end
	c1.WaitForThread();
	c2.WaitForThread();
	c3.WaitForThread();

	return 0;

}