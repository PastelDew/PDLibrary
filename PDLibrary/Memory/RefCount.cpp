#include "RefCount.h"

using namespace pdl::memory;

std::map<void*, refcnt> RefCount::REF_COUNT = std::map<void*, refcnt>();

void RefCount::Ref(void* ref) {
	if (REF_COUNT.count(ref) == 0)
		REF_COUNT[ref] = 1;
	else
		REF_COUNT[ref]++;
}

refcnt RefCount::Unref(void* ref) {
	refcnt cnt = --REF_COUNT[ref];
	if (cnt == 0)
		REF_COUNT.erase(ref);
	return cnt;
}