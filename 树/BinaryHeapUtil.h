//
// Created by Ko-chieh Yin on 10/6/25.
//

#ifndef STUDYDATASTRUCT_BINARYHEAPUTIL_H
#define STUDYDATASTRUCT_BINARYHEAPUTIL_H

#include "BinaryHeap.h"

//基于堆的 Top-K 选择算法（Heap-based Top-K Selection Algorithm）
//获取堆中优先级第i的元素(从1开始)
template<class T,class Compare>
T getValueWithOrderPriority(const BinaryHeap<T,Compare>& heap,std::size_t priority) {
    if (priority==0||priority>heap.size())
        throw std::runtime_error("优先级越界");
    MinBinaryHeap<T> aux;

    for (const auto& e:heap) {
        if (aux.size()<priority) {
            aux.push(e);
        }else if (e>aux.top()){
            aux.pop();
            aux.push(e);
        }
    }
    return aux.top();
}



#endif //STUDYDATASTRUCT_BINARYHEAPUTIL_H