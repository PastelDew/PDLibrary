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
	Ptr<T> obj = Create<T>();
	size_t size = sizeof(T);
	if (size > GetSize()) throw new Exception("Serialize::ReadClassType() error - Cannot read class. The buffer size is less than class <T>.");
	unsigned char databuffer = new unsigned char[size];
	for (int i = 0; i < size; i++)
		databuffer[i] = ReadUInt8();
	memcpy(obj.Ref(), databuffer, size);
	delete databuffer;
	return obj;
}