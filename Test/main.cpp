#include "pch.h"
#include "TestSources/TestIncludes.h"
#include <iostream>


int main(void) {
	TestBase* testCase;
	//testCase = (TestBase*) new TestByteRead();
	//testCase = (TestBase*) new TestMemoryPool();
	//testCase = (TestBase*) new TestArrayList();
	testCase = (TestBase*) new TestLinkedList();
	testCase->Run();

	return 0;
}