#ifndef _TESTBASE_H_
#define _TESTBASE_H_

#include <iostream>

class TestBase {
public:
	void Run() {
		std::cout << "The test case [" << GetTestName() << "] is generating..." << std::endl << std::endl;
		DoRun();
		std::cout << std::endl << "The test case [" << GetTestName() << "] was finished." << std::endl << std::endl;
	}

protected:
	virtual void DoRun() = 0;
	virtual const char* GetTestName() = 0;
};

#endif // End of _TESTBASE_H_