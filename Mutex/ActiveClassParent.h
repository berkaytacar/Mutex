#include "rt.h"
#include <atomic>
//#include "ActiveClassParent.h"

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

atomic_flag flag;


//Child1 thread is here
class Child1 : public ActiveClass {
private:
	int num;
	int main(void) {
		//printf("Child 1 is running\n");
		for (int i = 0; i < 50000; i++) {
			while (flag.test_and_set() == true)
				;
			MOVE_CURSOR(10, 20); // move cursor to cords [x,y] = (10, 20);
			printf("Child %d\n", num);
			fflush(stdout); // force output to be written to screen now
			flag.clear();
		}
		return 0;
	}

public:
	Child1(int _num) { num = _num; }

};


//Child2 thread is here (10,30)
class Child2 : public ActiveClass {
private:
	int num;
	int main(void) {
		for (int i = 0; i < 50000; i++) {
			while (flag.test_and_set() == true)
				;
			MOVE_CURSOR(10, 30);             	// move cursor to cords [x,y] = (10, 30);
			printf("Child %d\n", num);
			fflush(stdout);		      	// force output to be written to screen now
			flag.clear();
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
		for (int i = 0; i < 50000; i++) {
			while (flag.test_and_set() == true)
				;
			MOVE_CURSOR(10, 40);             	// move cursor to cords [x,y] = (10, 40);
			printf("Child %d\n", num);
			fflush(stdout);		      	// force output to be written to screen now
			flag.clear();
		}
		return 0;
	}

public:
	Child3(int _num) { num = _num; }

};

class ActiveClassParent : public ActiveClass {

	// put any attributes and member functions here that you like 
	// just like any other class along with any constructors and destructors
private:

	int MyNumber;

	//  Must override main() inherited from ActiveClass. The base class constructor will then
	//	create a thread execute main()
	int main(void) {
		flag.clear();
		// create the 3 other child threads
		Child1 c1(1);
		Child2 c2(2);
		Child3 c3(3);

		// allow childs to run
		c1.Resume();
		c2.Resume();
		c3.Resume();

		for (int i = 0; i < 50000; i++) {
			while (flag.test_and_set() == true)
				;
			MOVE_CURSOR(5, 5);             	// move cursor to cords [x,y] = 5,5
			printf("Thread 1");
			fflush(stdout);		      	// force output to be written to screen now
			flag.clear();
		}

		// wait for the 3 other child threads to end
		c1.WaitForThread();
		c2.WaitForThread();
		c3.WaitForThread();

		return 0;
	}

public:
	// here is the constructor for parent
	ActiveClassParent(int _MyNumber) { MyNumber = _MyNumber; }

};

