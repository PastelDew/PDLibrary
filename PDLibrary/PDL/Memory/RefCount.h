#ifndef _PDL_MEMORY_REFCOUNT_H_
#define _PDL_MEMORY_REFCOUNT_H_

#include "../PDCore.h"
#include <map>

namespace pdl {
	namespace memory {
		PDLDLL_API typedef unsigned long long refcnt;
		PDLDLL_EXTERN template class PDLDLL_API std::map<void*, refcnt>;
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

#endif // End of _PDL_MEMORY_REFCOUNT_H_