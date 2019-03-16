#include "pch.h"
#include "TestSources/TestIncludes.h"
//#include "PDLib/PDCore.h"
#include <iostream>

//using namespace pdl::memory;

#define TEST_SIZE 2
//Ptr<TestBase> TestList = new TestBase[TEST_SIZE][]{ new TestByteWrite() };

int main(void) {
	TestBase* testCase;
	//testCase = (TestBase*) new TestByteRead();
	//testCase = (TestBase*) new TestMemoryPool();
	testCase = (TestBase*) new TestArrayList();
	testCase->Run();

	return 0;
}