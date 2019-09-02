#include "include/TestIncludes.h"
#include <iostream>

int main(void) {
	LinkedList<Ptr<TestBase>> testCases;
	testCases
		<< new TestPtr()
		<< new TestArrayList()
		<< new TestLinkedList()
		<< new TestMemoryPool()
		;

	Ptr<TestBase> testCase;
	while (testCases.Size()) {
		testCases >> testCase;
		testCase->Run();
	}
	return 0;
}