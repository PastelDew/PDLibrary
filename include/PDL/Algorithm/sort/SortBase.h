#ifndef _PDL_ALGORITHM_SORT_SORTBASE_H_
#define _PDL_ALGORITHM_SORT_SORTBASE_H_

namespace pdl{
    namespace algorithm{
        namespace sort{
            template<typename T>
            class SortBase{
                public:
                virtual void Sort() = 0;
                virtual Ptr<T> Sorted() = 0;
            };
        }
    }
}

#endif // End of _PDL_ALGORITHM_SORT_SORTBASE_H_