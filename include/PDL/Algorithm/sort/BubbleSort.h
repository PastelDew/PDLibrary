#ifndef _PDL_ALGORITHM_SORT_BUBBLESORT_H_
#define _PDL_ALGORITHM_SORT_BUBBLESORT_H_
#include "pdl/PDCore.h"
#include "SortBase.h"
#include "pdl/Collection/ArrayList.h"

namespace pdl{
    namespace algorithm{
        namespace sort{
            template<typename T>
            class BubbleSort : public SortBase<T>, public ArrayList<T>{
                public:
                void Sort();
                Ptr<T> Sorted();
            };
        }
    }
}

#include "BubbleSort.hpp"

#endif // End of _PDL_ALGORITHM_SORT_BUBBLESORT_H_