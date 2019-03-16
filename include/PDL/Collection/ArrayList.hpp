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
	if (!this->arrayList) {
		size = 1;
		capacity = size * 2;
		arrayList = CreateList(capacity);
	}
	if (size >= capacity) {
		capacity = ++size * 2;
		Ptr<T> newList = CreateList(capacity);
		for (size_t i = 0; i < size - 1; i++)
			newList[i] = arrayList[i];
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