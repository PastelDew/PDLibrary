#include "../PDCore.h"
#include "MemoryPool.h"
#include "Ptr.h"

using namespace pdl::memory;

template<typename T>
T* Ptr<T>::Referer() const {
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
bool Ptr<T>::operator == (const Ptr<T>& ptr)  const {
	return mPtr == ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator == (const T* ptr)  const {
	return mPtr == ptr;
}

template<typename T>
bool Ptr<T>::operator == (const T& ptr)  const {
	return mPtr == &ptr;
}

template<typename T>
bool Ptr<T>::operator != (const Ptr<T>& ptr)  const {
	return mPtr != ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator != (const T* ptr)  const {
	return mPtr != ptr;
}

template<typename T>
bool Ptr<T>::operator != (const T& ptr)  const {
	return mPtr != &ptr;
}

template<typename T>
bool Ptr<T>::operator ! () const {
	return mPtr == NULL || mPtr == nullptr;
}

template<typename T>
bool Ptr<T>::operator < (const Ptr<T>& ptr) const {
	return mPtr < ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator > (const Ptr<T>& ptr) const {
	return mPtr > ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator <= (const Ptr<T>& ptr) const {
	return mPtr <= ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator >= (const Ptr<T>& ptr) const {
	return mPtr >= ptr.mPtr;
}

template<typename T>
bool Ptr<T>::operator < (const T* ptr) const {
	return mPtr < ptr;
}

template<typename T>
bool Ptr<T>::operator > (const T* ptr) const {
	return mPtr > ptr;
}

template<typename T>
bool Ptr<T>::operator <= (const T* ptr) const {
	return mPtr <= ptr;
}

template<typename T>
bool Ptr<T>::operator >= (const T* ptr) const {
	return mPtr >= ptr;
}

template<typename T>
T& Ptr<T>::operator [] (const size_t idx) const {
	return mPtr[idx];
}

template<typename T>
void Ptr<T>::SetTemp(bool isTemp) {
	this->isTemp = isTemp;
}

template<typename T>
bool Ptr<T>::IsTemp() {
	return isTemp;
}

template<typename T>
bool Ptr<T>::IsValid() {
	return mPtr != NULL && mPtr != nullptr;
}

/*
 * Private Functions
*/
template<typename T>
void Ptr<T>::Copy(const Ptr<T>& s) {
	this->Unref();
	mPtr = s.mPtr;
	this->Ref();
	isTemp = s.isTemp;
}

template<typename T>
void Ptr<T>::Copy(T* s) {
	this->Unref();
	mPtr = s;
	this->Ref();
}

template<typename T>
void Ptr<T>::Ref() {
	if (!IsValid()) return;
	RefCount::Ref(mPtr);
}

template<typename T>
void Ptr<T>::Unref() {
	if (IsValid() && RefCount::Unref(mPtr) == 0) {
		if (!this->isTemp)
			delete mPtr;
		else MemoryPool::Free(mPtr);
	}
}