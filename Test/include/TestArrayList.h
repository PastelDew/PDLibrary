#ifndef TEST_ARRAYLIST_H
#define TEST_ARRAYLIST_H

#include "TestBase.h"

#include <pdl/Collection/ArrayList.h>
#include <iostream>

using namespace pdl::collection;

class TestArrayList : public TestBase {
protected:
	const char* GetTestName() { return "ArrayList"; }

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
		ArrayList<_TestClass> arrayList;
		_TestClass a;
		a.val = 10;
		arrayList.Add(a);
		{
			_TestClass b;
			b.val = 20;
			arrayList.Add(b);
		}

		for (int i = 0; i < (int) arrayList.Size(); i++)
			arrayList[i].AddNPrint(0);
		
	}
};

#endif // End of TEST_MEMORY_POOL_H