#include "HTNode.h"

using namespace pdl::collection;

template<typename T>
HTNode<T>::HTNode(T& data, Ptr<HTNode<T> > head, Ptr<HTNode<T> > tail) {
	this->mHead = head;
	this->mTail = tail;
	this->mData = data;
}

template<typename T>
HTNode<T>::~HTNode() {
	this->Dispose();
}

template<typename T>
void HTNode<T>::Dispose() {
	this->mHead = NULL;
	this->mTail = NULL;
}

template<typename T>
void HTNode<T>::SetHead(Ptr<HTNode<T> > head) {
	this->mHead = head;
}
template<typename T>
void HTNode<T>::SetTail(Ptr<HTNode<T> > tail) {
	this->mTail = tail;
}
template<typename T>
void HTNode<T>::SetData(T& data) {
	this->mData = data;
}

template<typename T>
Ptr<HTNode<T>> HTNode<T>::GetHead() {
	return this->mHead;
}

template<typename T>
Ptr<HTNode<T>> HTNode<T>::GetTail() {
	return this->mTail;
}

template<typename T>
T& HTNode<T>::GetData() {
	return this->mData;
}