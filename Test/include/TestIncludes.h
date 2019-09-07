#ifndef TEST_INCLUDES_H
#define TEST_INCLUDES_H

#include <pdl/Collection/LinkedList.h>
#include "TestBase.h"

// >> Test Cases belows here <<

#include "TestPtr.h"
#include "TestLinkedList.h"
#include "TestMemoryPool.h"
#include "TestArrayList.h"
#include "TestRandom.h"

// >> Test Cases end point <<

#define TestCases TestCases
#define TEST_CASE_IMPORT \
LinkedList<Ptr<TestBase>> TestCases; \
TestCases \
<< new TestRandom() \
<< new TestArrayList() \
<< new TestLinkedList() \
<< new TestMemoryPool() \
<< new TestPtr() \
;

#endif