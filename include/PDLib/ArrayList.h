#ifndef _PDL_LIST_ARRAYLIST_H_
#define _PDL_LIST_ARRAYLIST_H_

#include "List.h"

namespace pdl {
	namespace list {
		template<typename T>
		class ArrayList : public List<T> {
		public:
			T & operator [] (int idx);
		};
		template <typename T>
		T& ArrayList<T>::operator [] (int idx) {
			return *this->Get(idx);
		}
	}
}

#endif // End of _PDL_LIST_ARRAYLIST_H_