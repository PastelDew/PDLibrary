#ifndef _PDL_LIST_LISTNONE_H_
#define _PDL_LIST_LISTNONE_H_

#include "PDCore.h"

using namespace pdl::memory;

namespace pdl {
	namespace list {
		template<typename T>
		class ListNode {
		private:
			Ptr<ListNode<T> >	mHead;
			Ptr<ListNode<T> >	mTail;
			Ptr<T>				mData;
		public:
			ListNode();
			ListNode(T& data, Ptr<ListNode<T>> head = NULL, Ptr<ListNode<T>> tail = NULL);
			~ListNode();
			void Dispose();
			void SetHead(Ptr<ListNode<T> > head);
			void SetTail(Ptr<ListNode<T> > tail);
			void SetData(T& data);
			Ptr<ListNode<T> > GetHead();
			Ptr<ListNode<T> > GetTail();
			Ptr<T> GetData();
		};
	}
}

#include "ListNode.hpp"

#endif // End of _PDL_LIST_LISTNONE_H_