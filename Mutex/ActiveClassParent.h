#pragma once
#include "rt.h"
//#include <atomic> //C++11 library
#include <mutex>
using namespace std;

// PARENT DECLARATION AND CHILD THREADS CAN BE FOUND BELOW

class ActiveClassParent : public ActiveClass
{

	// put any attributes and member functions here that you like 
	// just like any other class along with any constructors and destructors

private:

	int MyNumber;

	//  Must override main() inherited from ActiveClass. The base class constructor will then
	//	create a thread execute main()
	int main(void);

public:
	// here is the constructor for parent
	ActiveClassParent(int _MyNumber) { MyNumber = _MyNumber; }
	
};
/////////////////// CHILD THREADS ARE BELOW   /////////////////////////////

//Child1 thread is here
class Child1 : public ActiveClass {
private:
	int num;
	int main(void) {
		//printf("Child 1 is running\n");
		std:: mutex m1;
		for (int i = 0; i < 50000; i++) {
			//m1.lock(); // gain access to resource 
			lock_guard<mutex> theLock(m1);

			MOVE_CURSOR(10, 20); // move cursor to cords [x,y] = (10, 20);
			printf("Thread %d\n", num);
			fflush(stdout); // force output to be written to screen now
			//m1.unlock(); // let the resource go
		}
		return 0;
	}

public:
	Child1(int _num) { num = _num;}
	
};


//Child2 thread is here (10,30)
class Child2 : public ActiveClass {
private:
	int num;
	int main(void) {
		std::mutex m1;
		for (int i = 0; i < 50000; i++) {
			//m1.lock(); // gain access to resource
			lock_guard<mutex> theLock(m1);

			MOVE_CURSOR(10, 30);             	// move cursor to cords [x,y] = (10, 30);
			printf("Thread %d\n", num);
			fflush(stdout);		      	// force output to be written to screen now
			//m1.unlock(); // let the resource go
		}
		return 0;
	}

public:
	Child2(int _num) { num = _num; }

};


//Child3 thread is here (10,40)
class Child3 : public ActiveClass {
private:
	int num;
	int main(void) {
		std::mutex m1;
		for (int i = 0; i < 50000; i++) {
			//m1.lock(); // access to resource
			lock_guard<mutex> theLock(m1);
			MOVE_CURSOR(10, 40);             	// move cursor to cords [x,y] = (10, 40);
			printf("Thread %d\n", num);
			fflush(stdout);		      	// force output to be written to screen now
			//m1.unlock(); // let the resource go
		}
		return 0;
	}

public:
	Child3(int _num) { num = _num; }

};