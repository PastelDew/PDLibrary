#include "BubbleSort.h"
#include <iostream>

using namespace pdl::algorithm::sort;

template<typename T>
void BubbleSort<T>::Sort(){
    std::cout<<"SORT"<<std::endl;
}

template<typename T>
Ptr<T> BubbleSort<T>::Sorted(){
    std::cout<<"SORTED"<<std::endl;
    return Create<T>();
}