#ifndef _PDL_MEMORY_MEMORYPOOL_H_
#define _PDL_MEMORY_MEMORYPOOL_H_

#ifndef PDL_MEMORY_POOL_DEFAULT_SIZE
#define PDL_MEMORY_POOL_DEFAULT_SIZE 1024
#endif

#include "Ptr.h"

#include <map>
#include <mutex>

namespace pdl{
	namespace memory{
		PDLDLL_API class MemoryPool {
		public:
			typedef struct _MemoryBlock {
				Ptr<_MemoryBlock> parentBlock;
				Ptr<_MemoryBlock> prevBlock;
				size_t length;
				void* blockAddress;
			} MemoryBlock;

			template<class C>
			static Ptr<C> Allocate();

			template<class C>
			static Ptr<C> AllocateArray(size_t count);

			template <class C, typename... Args>
			static Ptr<C> Allocate(Args... args);

			PDLDLL_API static Ptr<uint8_t> Allocate(size_t size);

			template <typename T>
			static void Free(Ptr<T> obj);

			template <typename T>
			static void Free(T* obj);

			PDLDLL_API bool HasObject(void* obj);

		private:
			PDLDLL_API const static size_t SIZE_OF_MEMORY_BLOCK = sizeof(MemoryBlock);
			PDLDLL_API static MemoryPool* instance;
			std::mutex mMutex;

			size_t mBlockSize;
			map<Ptr<MemoryBlock>, size_t> mPages;
			map<Ptr<MemoryBlock>, size_t> mAvailableBlock;

		private:
			static void Initialize();
			MemoryPool();
			~MemoryPool() {}
			
			PDLDLL_API static MemoryPool* GetInstance();
			
			PDLDLL_API Ptr<MemoryBlock> AllocateBlock(size_t size);
			PDLDLL_API Ptr<MemoryBlock> GetNextBlock(Ptr<MemoryBlock> block);

			Ptr<MemoryBlock> AllocatePage();
			Ptr<MemoryBlock> FindFreeBlock(size_t size);
			bool HasNextBlock(Ptr<MemoryBlock> block);
		};
		//PDLDLL_EXTERN template class PDLDLL_API Ptr<MemoryPool::MemoryBlock>;
		PDLDLL_EXTERN template class PDLDLL_API Ptr<uint8_t>;
	}
}

#include "MemoryPool.hpp"

#endif // End of _PDL_MEMORY_MEMORYPOOL_H_