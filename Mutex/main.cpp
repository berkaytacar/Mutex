#include "ActiveClassParent.h"
#include "rt.h"
using namespace std;

int main(void)
{
	// create instance of the above active object on the stack
	// then allow it to run and then wait for it to terminate

	ActiveClassParent Object1(1);
	Object1.Resume();				// allow thread to run
	


	Object1.WaitForThread(); // wait for thread to finish
	

	cout << "Finished\n";

	// object1/2 destructor called at the end of program main()

	return 0;
}