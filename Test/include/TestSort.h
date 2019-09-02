#ifndef TEST_SORT_H
#define TEST_SORT_H

#include "TestBase.h"

#include <pdl/Algorithm/sort/BubbleSort.h>
#include <iostream>

using namespace pdl::collection;

class TestSort : public TestBase {
protected:
	const char* GetTestName() { return "Sort"; }

	void DoRun() {
		BubbleSort<int> sort;
        sort.Sort();
	}
};

#endif // End of TEST_SORT_H