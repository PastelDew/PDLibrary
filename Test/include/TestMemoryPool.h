#ifndef TEST_MEMORY_POOL_H
#define TEST_MEMORY_POOL_H

#include "TestBase.h"

#include <pdl/Memory/MemoryPool.h>
#include <iostream>

using namespace pdl::memory;

class TestMemoryPool : public TestBase {
protected:
	const char* GetTestName() { return "MemoryPool"; }

	class _TestClass {
	public:
		int val;
		_TestClass() {
			val = 5;
			std::cout << "Constructed Test Class" << std::endl;
		}
		
		void AddNPrint(int data) {
			std::cout << (val + data) << std::endl;
		}
	};


	void DoRun() {
		Ptr<uint8_t> ptr = MemoryPool::Allocate(10);
		for (int i = 0; i < 10; i++)
			ptr[i] = i;

		for (int i = 0; i < 10; i++)
			std::cout << (char)(ptr[i] + 'A') << std::endl;

		MemoryPool::Free(ptr.Referer());

		Ptr<_TestClass> test = MemoryPool::Allocate<_TestClass>();
		test->AddNPrint(10);
		MemoryPool::Free(test);
	}
};

#endif // End of TEST_MEMORY_POOL_H