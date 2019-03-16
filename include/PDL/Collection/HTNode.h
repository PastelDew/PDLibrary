#ifndef _PDL_COLLECTION_HTNODE_H_
#define _PDL_COLLECTION_HTNODE_H_

#include "../PDCore.h"

using namespace pdl::memory;

namespace pdl {
	namespace collection {
		template<typename T>
		class HTNode {
		private:
			Ptr<HTNode<T> >	mHead;
			Ptr<HTNode<T> >	mTail;
			T				mData;
		public:
			HTNode() {}
			HTNode(T& data, Ptr<HTNode<T>> head = NULL, Ptr<HTNode<T>> tail = NULL);
			~HTNode();
			void Dispose();
			void SetHead(Ptr<HTNode<T> > head);
			void SetTail(Ptr<HTNode<T> > tail);
			void SetData(T& data);
			Ptr<HTNode<T> > GetHead();
			Ptr<HTNode<T> > GetTail();
			T& GetData();
		};
	}
}

#include "HTNode.hpp"

#endif // End of _PDL_COLLECTION_HTNODE_H_