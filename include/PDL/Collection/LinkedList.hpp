#include "LinkedList.h"

using namespace pdl::collection;
using namespace pdl::memory;

template<typename T>
LinkedList<T>::LinkedList() {
	this->mFirst = CreateNode();
	this->mLast = this->mFirst;
	this->mSize = 0;
}

template<typename T>
Ptr<HTNode<T> > LinkedList<T>::CreateNode() {
	return MemoryPool::Allocate<HTNode<T> >();
}

template<typename T>
Ptr<HTNode<T> > LinkedList<T>::GetNode(size_t idx) {
	if (idx >= this->mSize) return nullptr;
	Ptr<HTNode<T> > node;
	
	if (idx < mSize / 2) {
		node = this->mFirst;
		for (size_t i = 0; i < idx; i++)
			node = node->GetTail();
	}
	else {
		node = this->mLast;
		for (size_t i = mSize - 1; i > idx; i--)
			node = node->GetHead();
	}
	
	return node;
}

template<typename T>
void LinkedList<T>::Insert(T& data, size_t idx) {
	if (idx == this->mSize && this->mSize == 0) { this->Append(data); return; }
	if (idx >= this->mSize) throw new Exception("List-Add Failed. The required index is larger than list size.");

	Ptr<HTNode<T> > node = this->mFirst;
	for (size_t i = 1; i <= idx; i++) node = node->GetTail();
	Ptr<HTNode<T> > newNode = CreateNode();
	newNode->SetData(data);
	newNode->SetHead(node->GetHead());
	newNode->SetTail(node);
	node->GetHead()->SetTail(newNode);
	node->SetHead(newNode);
	this->mSize++;
}

template<typename T>
void LinkedList<T>::Append(T& data) {
	Ptr<HTNode<T> > newNode;
	if (mSize == 0)
		newNode = this->mFirst;
	else {
		newNode = CreateNode();
		newNode->SetHead(this->mLast);
	}
	newNode->SetData(data);

	if (this->mSize > 0)
		this->mLast->SetTail(newNode);
	
	this->mLast = newNode;
	this->mSize++;
}

template<typename T>
void LinkedList<T>::Remove(T& dataz) {
	size_t i = 0;
	Ptr<HTNode<T> > node = this->mFirst;
	while(!!node->GetTail()) {
		if (node->GetData()->Ref() == &data) {
			node->GetHead()->SetTail(node->GetTail());
			node->GetTail()->SetHead(node->GetHead());
			this->mSize--;
		}
		node = node->GetTail();
		i++;
	}
}

template<typename T>
void LinkedList<T>::RemoveAt(size_t idx) {
	if (idx >= (int)this->mSize) return;
	if (mSize == 1) {
		this->mFirst = CreateNode();
		this->mLast = this->mFirst;
		this->mSize = 0;
		return;
	}
	Ptr<HTNode<T> > node = GetNode(idx);
	Ptr<HTNode<T> > head = node->GetHead();
	Ptr<HTNode<T> > tail = node->GetTail();
	if (!!head) head->SetTail(tail);
	else this->mFirst = tail;
	if (!!tail) tail->SetHead(head);
	else this->mLast = head;
	node->Dispose();
	this->mSize--;
}

template<typename T>
T& LinkedList<T>::Get(size_t idx) {
	return GetNode(idx)->GetData();
}

template<typename T>
T& LinkedList<T>::operator[](size_t idx) {
	return Get(idx);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator << (const T& data) {
	T nonConstData = data;
	Append(nonConstData);
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator >> (T& data) {
	data = mLast->GetData();
	RemoveAt(mSize - 1);
	return *this;
}

template<typename T>
void LinkedList<T>::Clear() {
	while (mSize > 0)
		RemoveAt(0);
}

template<typename T>
size_t LinkedList<T>::Size() {
	return this->mSize;
}