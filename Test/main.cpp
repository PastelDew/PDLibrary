#include "TestBase.h"
#include "TestByteRead.h"
#include <iostream>

int main(void) {
	TestBase* testCase = (TestBase*) new TestByteRead();
	testCase->Run();
	system("pause");
	return 0;
}