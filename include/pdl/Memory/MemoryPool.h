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
			std::map<Ptr<MemoryBlock>, size_t> mPages;
			std::map<Ptr<MemoryBlock>, size_t> mAvailableBlock;

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
		PDLDLL_EXTERN template class PDLDLL_API Ptr<MemoryPool::MemoryBlock>;
		PDLDLL_EXTERN template class PDLDLL_API Ptr<uint8_t>;

		template<typename T>
		static Ptr<T> Create() { return MemoryPool::Allocate<T>(); }
		template<typename T, typename... Args>
		static Ptr<T> Create(Args... args) { return MemoryPool::Allocate<T>(args); }
		template<typename T>
		static Ptr<T> CreateArray(size_t count) { return MemoryPool::AllocateArray<T>(count); }
		/*template<typename T, typename A1>
		static Ptr<T> Create(A1 a1) { return Ptr<T>(new T(a1)); }
		template<typename T, typename A1, typename A2>
		static Ptr<T> Create(A1 a1, A2 a2) { return Ptr<T>(new T(a1, a2)); }
		template<typename T, typename A1, typename A2, typename A3>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3) { return Ptr<T>(new T(a1, a2, a3)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4) { return Ptr<T>(new T(a1, a2, a3, a4)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return Ptr<T>(new T(a1, a2, a3, a4, a5)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) { return Ptr<T>(new T(a1, a2, a3, a4, a5, a6)); }
		template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
		static Ptr<T> Create(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) { return Ptr<T>(new T(a1, a2, a3, a4, a5, a6, a7)); }*/
	}
}

PDLDLL_EXTERN template class PDLDLL_API std::map<pdl::memory::Ptr<pdl::memory::MemoryPool::MemoryBlock>, size_t>;
#include "MemoryPool.hpp"

#endif // End of _PDL_MEMORY_MEMORYPOOL_H_