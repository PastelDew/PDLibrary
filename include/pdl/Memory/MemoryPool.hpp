#include "MemoryPool.h"
#include <assert.h>

using namespace pdl::memory;

template<class C>
Ptr<C> MemoryPool::Allocate() {
	Ptr<MemoryBlock> block = GetInstance()->AllocateBlock(sizeof(C));
	C* obj = new(block->blockAddress) C();
	block.Ref();
	return Ptr<C>(obj, true);
}

template<class C>
Ptr<C> MemoryPool::AllocateArray(size_t count) {
	assert(count > 0);
	Ptr<MemoryBlock> block = GetInstance()->AllocateBlock(sizeof(C) * count);
	C* obj = (C*)block->blockAddress;
	block.Ref();
	return Ptr<C>(obj, true);
}

template <class C, typename... Args>
Ptr<C> MemoryPool::Allocate(Args... args) {
	Ptr<MemoryBlock> block = GetInstance()->AllocateBlock(sizeof(C));
	//C* obj = new(block->blockAddress) C(args);
	C* obj = {new(block->blockAddress) C(args)...};
	block.Ref();
	return Ptr<C>(obj, true);
}

template <typename T>
void MemoryPool::Free(Ptr<T> obj) {
	Free(obj.Referer());
}

template <typename T>
void MemoryPool::Free(T* obj) {
	MemoryPool* mem = GetInstance();
	if (mem->HasObject(obj)) {
		Ptr<MemoryBlock> block((MemoryBlock*)((size_t)obj - SIZE_OF_MEMORY_BLOCK), true);
		mem->mMutex.lock();
		if (mem->mAvailableBlock.count(block) > 0)
			mem->mAvailableBlock.erase(block);
		else
			obj->~T();

		if (mem->mAvailableBlock.count(block->prevBlock)) {
			Ptr<MemoryBlock> prevBlock(block->prevBlock, true);
			mem->mAvailableBlock.erase(prevBlock);
			prevBlock->length += block->length + SIZE_OF_MEMORY_BLOCK;
			block = prevBlock;
		}

		Ptr<MemoryBlock> nextBlock = mem->GetNextBlock(block);
		if (!!nextBlock && mem->mAvailableBlock.count(nextBlock)) {
			mem->mAvailableBlock.erase(nextBlock);
			block->length += nextBlock->length + SIZE_OF_MEMORY_BLOCK;
		}

		mem->mAvailableBlock[block] = block->length;
		mem->mMutex.unlock();
	}
}