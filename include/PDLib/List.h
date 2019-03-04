#ifndef _PDL_LIST_LIST_H_
#define _PDL_LIST_LIST_H_

#include "ListNode.h"

namespace pdl {
	namespace list {
		template<typename T>
		class List {
		protected:
			Ptr<ListNode<T> > mFirst;
			Ptr<ListNode<T> > mLast;
			size_t mSize;

			void Append();
		public:
			List(size_t capacity = 0);
			void Add(T& data, int idx = -1);
			void Append(T& data);
			void Remove(T& data);
			void RemoveAt(int idx);
			T* Get(int idx);
			void Clear();
			size_t Size();
		};
	}
}

#include "List.hpp"

#endif // End of _PDL_LIST_LIST_H_