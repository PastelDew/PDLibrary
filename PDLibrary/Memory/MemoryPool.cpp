#include "MemoryPool.h"
#include "Ptr.h"
using namespace pdl::memory;

MemoryPool* MemoryPool::instance = nullptr;

MemoryPool::MemoryPool() {
	mBlockSize = PDL_MEMORY_POOL_DEFAULT_SIZE + SIZE_OF_MEMORY_BLOCK;
	AllocatePage();
}

Ptr<MemoryPool::MemoryBlock> MemoryPool::AllocatePage() {
	Ptr<MemoryBlock> memBlock((MemoryBlock*) new uint8_t[mBlockSize]);
	memBlock->parentBlock = memBlock;
	memBlock->prevBlock = nullptr;
	memBlock->length = mBlockSize - SIZE_OF_MEMORY_BLOCK;
	memBlock->blockAddress = (void*)((size_t)memBlock.Referer() + SIZE_OF_MEMORY_BLOCK);
	mPages[memBlock] = memBlock->length;
	mAvailableBlock[memBlock] = memBlock->length;
	return memBlock;
}

Ptr<MemoryPool::MemoryBlock> MemoryPool::AllocateBlock(size_t size) {
	mMutex.lock();
	Ptr<MemoryBlock> block(FindFreeBlock(size), true);

	if (!block) {
		if (mBlockSize < size * 2) {
			size_t temp = mBlockSize;
			mBlockSize = (size + SIZE_OF_MEMORY_BLOCK) * 2;
			block = AllocatePage();
			mBlockSize = temp;
		}
		else block = AllocatePage();
	}

	mAvailableBlock.erase(block);
	if (size < block->length) {
		Ptr<MemoryBlock> nextBlock = GetNextBlock(block);
		Ptr<MemoryBlock> newBlock((MemoryBlock*)((size_t)block.Referer() + SIZE_OF_MEMORY_BLOCK + size), true);

		newBlock->parentBlock = block->parentBlock;
		newBlock->length = block->length - SIZE_OF_MEMORY_BLOCK - size;
		newBlock->blockAddress = (void*)((size_t)newBlock.Referer() + SIZE_OF_MEMORY_BLOCK);

		newBlock->prevBlock = block;
		if (nextBlock.IsValid())
			nextBlock->prevBlock = newBlock;

		block->length = size;
		mAvailableBlock[newBlock] = newBlock->length;
	}
	mMutex.unlock();
	return block;
}

Ptr<MemoryPool::MemoryBlock> MemoryPool::FindFreeBlock(size_t size) {
	size_t requiredSize = size + SIZE_OF_MEMORY_BLOCK;
	for (map<Ptr<MemoryBlock>, size_t>::iterator it = mAvailableBlock.begin(); it != mAvailableBlock.end(); it++) {
		if (it->second > requiredSize) {
			return it->first;
		}
	}
	return nullptr;
}

bool MemoryPool::HasObject(void* obj) {
	for (map<Ptr<MemoryBlock>, size_t>::iterator it = mPages.begin(); it != mPages.end(); it++) {
		MemoryBlock* pPage = it->first.Referer();
		if (pPage == (MemoryBlock*)((size_t)obj - SIZE_OF_MEMORY_BLOCK)) return true; // isParent?
		else if (pPage < obj && obj <= (void*)((size_t)pPage + SIZE_OF_MEMORY_BLOCK + mPages[pPage])) {
			MemoryBlock* block = (MemoryBlock*)((size_t)obj - SIZE_OF_MEMORY_BLOCK);
			return block->blockAddress == obj;
		}
	}
	return false;
}

bool MemoryPool::HasNextBlock(Ptr<MemoryBlock> block) {
	Ptr<MemoryBlock> parentBlock(block->parentBlock, true);
	size_t nextBlockOffset = (size_t)block.Referer() - (size_t)parentBlock.Referer() + SIZE_OF_MEMORY_BLOCK + block->length + 1;
	return nextBlockOffset + SIZE_OF_MEMORY_BLOCK/*Required header of next block*/
		< /*at least 1 byte for object*/
		SIZE_OF_MEMORY_BLOCK + mPages[parentBlock];
}

Ptr<MemoryPool::MemoryBlock> MemoryPool::GetNextBlock(Ptr<MemoryBlock> block) {
	Ptr<MemoryBlock> parentBlock(block->parentBlock, true);
	size_t nextBlockOffset = (size_t)block.Referer() - (size_t)parentBlock.Referer() + SIZE_OF_MEMORY_BLOCK + block->length;
	bool hasNextBlock = nextBlockOffset + SIZE_OF_MEMORY_BLOCK/*Required header of next block*/
		< /*at least 1 byte for object*/
		SIZE_OF_MEMORY_BLOCK + mPages[parentBlock];
	if (hasNextBlock)
		return Ptr<MemoryBlock>((MemoryBlock*)((size_t)parentBlock.Referer() + nextBlockOffset), true);
	else
		return nullptr;
}

//-----------------------------------------------
// static functions begin
//-----------------------------------------------

MemoryPool* MemoryPool::GetInstance() {
	Initialize();
	return instance;
}

Ptr<uint8_t> MemoryPool::Allocate(size_t size) {
	Ptr<MemoryBlock> block = GetInstance()->AllocateBlock(size);
	return Ptr<uint8_t>((uint8_t*)block->blockAddress, true);
}

void MemoryPool::Initialize() {
	if (!instance)
		instance = new MemoryPool();
}