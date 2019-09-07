#include "include/TestIncludes.h"

int main(void) {
	TEST_CASE_IMPORT

	Ptr<TestBase> testCase;
	while (TestCases.Size()) {
		TestCases >> testCase;
		testCase->Run();
	}
#if defined(WIN32) || defined(_MSC_VER)
	system("pause");
#endif
	return 0;
}