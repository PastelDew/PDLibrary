#include "Serialize.h"

using namespace pdl::collection;

template<typename T>
void Serialize::WriteObject(T data) {
	uint8_t * pData = &data;
	size_t size = sizeof(T);
	for (size_t i = 0; i < size; i++)
		WriteUInt8(pData[i]);
}
template<typename T>
Ptr<T> Serialize::ReadObject() {
	size_t size = sizeof(T);
	if (size > buffer.Size())
		throw new Exception("Serialize::ReadClassType() error - Cannot read class. The buffer size is less than class <T>.");
	Ptr<T> obj = MemoryPool::Allocate<T>();
	uint8_t * pObj = obj.Referer();
	for (size_t i = 0; i < size; i++)
		pObj[i] = ReadUInt8();
}