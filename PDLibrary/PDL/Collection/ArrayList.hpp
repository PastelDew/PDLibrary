#include "../PDCore.h"
#include "ArrayList.h"
#include "../Memory/MemoryPool.h"
#include "../Debug/Exception.h"

using namespace pdl::collection;
using namespace pdl::memory;

template<typename T>
ArrayList<T>::ArrayList(size_t capacity) {
	this->size = 0;
	this->capacity = capacity;
	arrayList = CreateList(capacity);
}

template<typename T>
Ptr<T> ArrayList<T>::CreateList(size_t size) {
	Ptr<T> list;
	if (size != 0)
		list = MemoryPool::AllocateArray<T>(size);
	return list;
}

template<typename T>
size_t ArrayList<T>::Size() {
	return size;
}

template<typename T>
T& ArrayList<T>::operator[](int index) {
	return this->Get(index);
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator<<(T& arrayList) {
	this->Add(arrayList);
	return *this;
}


template<typename T>
void ArrayList<T>::Add(T& obj) {
	if (size >= capacity) {
		capacity = (size + 1) * 2;
		Ptr<T> newList = CreateList(capacity);
		memcpy_s(newList.Referer(), size, arrayList.Referer(), size);
		this->arrayList = newList;
	}
	this->arrayList[size++] = obj;
}

template<typename T>
void ArrayList<T>::Remove(T& obj) {
	int idx = IndexOf(obj);
	if (idx < 0) return;
	RemoveAt(idx);
}

template<typename T>
void ArrayList<T>::RemoveAt(int index) {
	if (index < 0) index = size - index - 1;
	if (index < 0 || index >= capacity)
		return;
	while (index < size - 1)
		this->arrayList[index] = this->arrayList[++index];
	this->arrayList[size--] = nullptr;
}

template<typename T>
void ArrayList<T>::RemoveRange(size_t index, size_t size) {
	if (index + size > this->size)
		throw new Exception("ArrayList<T>::RemoveRange - Out of range!");
	size_t tailSize = this->size - size - index;
	if (tailSize > 0)
		memcpy_s(arrayList.Referer() + index, tailSize, arrayList.Referer() + index + size, tailSize);
	memset(arrayList.Referer() + index + tailSize, this->size - index - tailSize);
	this->size -= size;
}

template<typename T>
void ArrayList<T>::Clear() {
	size = 0;
	capacity = 10;
	arrayList = CreateList(capacity);
}

template<typename T>
T& ArrayList<T>::Get(int index) {
	if (index < 0) index = size - index - 1;
	if (index < 0 || (size_t)index >= capacity)
		throw new Exception("The given index is out of range!");
	return arrayList[index];
}

template<typename T>
int ArrayList<T>::IndexOf(T& obj) {
	for (int i = 0; i < size; i++) {
		if (this->arrayList[i] == obj)
			return i;
	}
	return -1;
}