#include "include/TestIncludes.h"
#include <iostream>

int main(void) {
	LinkedList<Ptr<TestBase>> testCases;
	testCases << new TestMemoryPool() << new TestArrayList() << new TestLinkedList();

	Ptr<TestBase> testCase;
	while (testCases.Size()) {
		testCases >> testCase;
		testCase->Run();
	}
	return 0;
}