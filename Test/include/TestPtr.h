#ifndef TEST_PTR_H
#define TEST_PTR_H

#include "TestBase.h"

#include "pdl//Memory/Ptr.h"
#include <iostream>

using namespace pdl::memory;

class TestPtr : public TestBase {
protected:
	const char* GetTestName() { return "Ptr"; }

	class _TestClass {
	public:
		int val;
		_TestClass() {
			val = 5;
			std::cout << "Constructed Test Class" << std::endl;
		}

		~_TestClass() {
			val = 0;
			std::cout << "Destructed Test Class" << std::endl;
		}

		void AddNPrint(int data) {
			std::cout << (val + data) << std::endl;
		}
	};


	void DoRun() {
		Ptr<_TestClass> pTest;
		pTest = new _TestClass();
		pTest->val = 10;
		pTest->AddNPrint(0);
	}
};

#endif // End of TEST_PTR_H