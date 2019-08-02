#ifndef _PDL_COLLECTION_LINKEDLIST_H_
#define _PDL_COLLECTION_LINKEDLIST_H_

#include "../PDCore.h"
#include "HTNode.h"

namespace pdl {
	namespace collection {
		template<typename T>
		class LinkedList {
		protected:
			Ptr<HTNode<T> > mFirst;
			Ptr<HTNode<T> > mLast;
			size_t mSize;

			Ptr<HTNode<T> > CreateNode();
			Ptr<HTNode<T> > GetNode(size_t idx);
		public:
			LinkedList();
			void Insert(T& data, size_t idx);
			void Append(T& data);
			void Remove(T& data);
			void RemoveAt(size_t idx);
			void RemoveRange(size_t idx, size_t size);
			T& Get(size_t idx);
			T& operator [](size_t idx);
			LinkedList& operator << (const T& data);
			LinkedList& operator >> (T& data);
			void Clear();
			size_t Size();
		};
	}
}

#include "LinkedList.hpp"

#endif // End of _PDL_COLLECTION_LINKEDLIST_H_