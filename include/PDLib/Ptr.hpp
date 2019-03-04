#include "Ptr.h"

using namespace pdl::memory;

template<typename T>
T* Ptr<T>::Ref() {
	return mPtr;
}

template<typename T>
Ptr<T>& Ptr<T>::operator =(Ptr<T> ptr) {
	Copy(ptr); return *this;
}

template<typename T>
Ptr<T>& Ptr<T>::operator =(T* ptr) {
	Copy(ptr); return *this;
}

template<typename T>
T& Ptr<T>::operator *() {
	return *mPtr;
}

template<typename T>
T* Ptr<T>::operator ->() {
	return mPtr;
}

template<typename T>
bool Ptr<T>::operator == (Ptr<T>& ptr) {
	return mPtr == ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator == (T* ptr) {
	return mPtr == ptr;
}

template<typename T>
bool Ptr<T>::operator == (T& ptr) {
	return mPtr == &ptr;
}

template<typename T>
bool Ptr<T>::operator != (Ptr<T>& ptr) {
	return mPtr != ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator != (T* ptr) {
	return mPtr != ptr;
}

template<typename T>
bool Ptr<T>::operator != (T& ptr) {
	return mPtr != &ptr;
}

template<typename T>
bool Ptr<T>::operator ! () {
	return (mPtr == NULL) ? true : false;
}

template<typename T>
T& Ptr<T>::operator [] (size_t idx) {
	return mPtr[idx];
}

template<typename T>
void Ptr<T>::SetTemp(bool isTemp) {
	this->isTemp = isTemp;
}

template<typename T>
bool Ptr<T>::IsValid() {
	return mPtr != NULL;
}