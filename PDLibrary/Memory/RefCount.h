#ifndef _PDL_MEMORY_REFCOUNT_H_
#define _PDL_MEMORY_REFCOUNT_H_

#include "../PDCore.h"
#include <map>

namespace pdl {
	namespace memory {
		typedef unsigned long long refcnt;
		
		class RefCount {
		public:
			PDLDLL_API static void Ref(void* ref);
			PDLDLL_API static refcnt Unref(void* ref);

		private:
			RefCount() {}
			PDLDLL_API static std::map<void*, refcnt> REF_COUNT;
		};
	}
}

PDLDLL_EXTERN template class PDLDLL_API std::map<void*, pdl::memory::refcnt>;

#endif // End of _PDL_MEMORY_REFCOUNT_H_