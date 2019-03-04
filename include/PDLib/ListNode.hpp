#include "ListNode.h"

using namespace pdl::list;

template<typename T>
ListNode<T>::ListNode() {
	this->mHead = NULL;
	this->mTail = NULL;
	this->mData = NULL;
}

template<typename T>
ListNode<T>::ListNode(T& data, Ptr<ListNode<T> > head, Ptr<ListNode<T> > tail) {
	this->mHead = head;
	this->mTail = tail;
	this->mData = data;
}

template<typename T>
ListNode<T>::~ListNode() {
	this->Dispose();
}

template<typename T>
void ListNode<T>::Dispose() {
	this->mHead = NULL;
	this->mTail = NULL;
	this->mData = NULL;
}

template<typename T>
void ListNode<T>::SetHead(Ptr<ListNode<T> > head) {
	this->mHead = head;
}
template<typename T>
void ListNode<T>::SetTail(Ptr<ListNode<T> > tail) {
	this->mTail = tail;
}
template<typename T>
void ListNode<T>::SetData(T& data) {
	this->mData = &data;
}

template<typename T>
Ptr<ListNode<T>> ListNode<T>::GetHead() {
	return this->mHead;
}

template<typename T>
Ptr<ListNode<T>> ListNode<T>::GetTail() {
	return this->mTail;
}

template<typename T>
Ptr<T> ListNode<T>::GetData() {
	return this->mData;
}