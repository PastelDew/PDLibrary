#include "List.h"

using namespace pdl::list;

template<typename T>
List<T>::List(size_t capacity) {
	if (capacity == 0) return;
	this->mFirst = Create<ListNode<T> >();
	this->mLast = this->mFirst;
	for (size_t i = 1; i < capacity; i++) this->Append();
}

template<typename T>
void List<T>::Add(T& data, int idx) {
	if (idx < 0) { this->Append(data); return; }
	if (idx == this->mSize && this->mSize == 0) { this->Append(data); return; }
	if (idx >= this->mSize) throw new Exception("List-Add Failed. The required index is larger than list size.");

	Ptr<ListNode<T> > node = this->mFirst;
	for (int i = 1; i <= idx; i++) node = node->mTail;
	Ptr<ListNode<T> > newNode = Create<ListNode<T> >();
	newNode->SetData(data);
	newNode->SetHead(node->GetHead());
	newNode->SetTail(node);
	node->GetHead()->SetTail(newNode);
	node->SetHead(newNode);
	this->mSize++;
}

template<typename T>
void List<T>::Append() {
	Ptr<ListNode<T> > newNode = Create<ListNode<T> >();
	newNode->SetHead(this->mLast);
	this->mLast->SetTail(newNode);
	this->mLast = newNode;
	this->mSize++;
}

template<typename T>
void List<T>::Append(T& data) {
	Ptr<ListNode<T> > newNode = Create<ListNode<T> >();
	newNode->SetHead(this->mLast);
	newNode->SetData(data);
	if (this->mSize > 0) this->mLast->SetTail(newNode);
	else this->mFirst = newNode;
	this->mLast = newNode;
	this->mSize++;
}

template<typename T>
void List<T>::Remove(T& dataz) {
	size_t i = 0;
	Ptr<ListNode<T> > node = this->mFirst;
	do {
		if (node->GetData()->Ref() == &data) {
			node->GetHead()->SetTail(node->GetTail());
			node->GetTail()->SetHead(node->GetHead());
			this->mSize--;
		}
		node = node->GetTail();
		i++;
	} while (i < this->mSize);
}

template<typename T>
void List<T>::RemoveAt(int idx) {
	if (idx >= (int)this->mSize) return;
	Ptr<ListNode<T> > node = this->mFirst;
	for (int i = 1; i <= idx; i++) node = node->GetTail();
	node->GetHead()->SetTail(node->GetTail());
	node->GetTail()->SetHead(node->GetHead());
	this->mSize--;
}

template<typename T>
T* List<T>::Get(int idx) {
	if (idx >= (int)this->mSize) return NULL;
	Ptr<ListNode<T> > node = this->mFirst;
	for (int i = 1; i <= idx; i++) node = node->GetTail();
	Ptr<T> data = node->GetData();
	return data.Ref();
}

template<typename T>
void List<T>::Clear() {
	Ptr<ListNode<T> > node = this->mFirst;
	for (size_t i = 1; i < this->mSize; i++) {
		node = node->GetTail();
		node->GetHead()->Dispose();
	}
	this->mFirst = NULL;
	this->mLast = NULL;
	this->mSize = 0;
}

template<typename T>
size_t List<T>::Size() {
	return this->mSize;
}