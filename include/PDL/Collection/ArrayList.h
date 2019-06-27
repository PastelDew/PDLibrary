#ifndef _PDL_COLLECTION_ARRAYLIST_H_
#define _PDL_COLLECTION_ARRAYLIST_H_

#include "../PDCore.h"

namespace pdl {
	namespace collection {
		template<typename T>
		class ArrayList {
		private:
			size_t size, capacity;
			Ptr<T> arrayList;

			Ptr<T> CreateList(size_t size);
		public:
			ArrayList(size_t capacity = 10);

			void Add(T& obj);
			void Remove(T &obj);
			void RemoveAt(int index);
			void Clear();
			T& Get(int index);

			size_t Size();
			int IndexOf(T& obj);

			T& operator[](int index);

			ArrayList<T>& operator<<(T& obj);
		};
	}
}

#include "ArrayList.hpp"

#endif // End of _PDL_COLLECTION_ARRAYLIST_H_