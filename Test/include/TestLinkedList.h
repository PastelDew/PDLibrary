#ifndef TEST_LINKEDLIST_H
#define TEST_LINKEDLIST_H

#include "TestBase.h"

#include <PDL/Collection/LinkedList.h>
#include <iostream>

using namespace pdl::collection;

class TestLinkedList : public TestBase {
protected:
	const char* GetTestName() { return "LinkedList"; }

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
		LinkedList<_TestClass> list;
		{
			_TestClass a;
			a.val = 10;
			list.Append(a);
			{
				_TestClass b;
				b.val = 20;
				list.Append(b);
			}

			_TestClass c;
			c.val = 30;
			list.Insert(c, 1);

			for (size_t i = 0; i < list.Size(); i++)
				list.Get(i).AddNPrint(0);
		}
		list.Clear();
	}
};

#endif // End of TEST_LINKEDLIST_H