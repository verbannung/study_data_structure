//
// Created by Ko-chieh Yin on 10/6/25.
//

#ifndef STUDYDATASTRUCT_BINARYHEAP_H
#define STUDYDATASTRUCT_BINARYHEAP_H
#include "Heap.h"
#include "BinaryTreeUtil.h"

//数组实现
//为什么需要用数组而不是链表? 因为完全二叉树可以通过下标确定父节点等信息,而链表查询速度会退化到O(n)

template<class T,class Compare=std::less<T>>
class BinaryHeap:public Heap<T> {


protected:
    std::vector<T> data;

    Compare compare;

    void heapifyUp(std::size_t index);

    void heapifyDown(std::size_t index);
public:
    explicit BinaryHeap(Compare compare_=Compare{});

    explicit BinaryHeap(TreeIterator<T>& iterator_,Compare compare_=Compare{});

    [[nodiscard]] bool empty() const override;

    [[nodiscard]] std::size_t size() const override;

    [[nodiscard]] std::size_t depth() const override;

    void push(const T &element)  override;

    void pop()  override;

    const T & top() const override;

    void clear()  override;

     // bool compare(const T &a, const T &b) const override {
     //     return comp(a,b);
     // };

    auto begin() const;

    auto end() const;
};

//上浮
template<class T,class Compare>
void BinaryHeap<T,Compare>::heapifyUp(std::size_t index) {
    while (index>0) {
        std::size_t parentIndex = (index-1)/2;
        if (this->compare(data[parentIndex],data[index]))
            break;
        std::swap(data[parentIndex],data[index]);
        index = parentIndex;
    }
}

template<class T,class Compare>
void BinaryHeap<T,Compare>::heapifyDown(std::size_t index) {
    auto size = data.size();
    while (true) {
        std::size_t leftChildIndex = 2*index+1;
        std::size_t rightChildIndex = 2*index+2;
        std::size_t currentIndex=index;
        if (leftChildIndex<size &&this->compare(data[leftChildIndex],data[currentIndex])) {
            currentIndex = leftChildIndex;
        }
        if (rightChildIndex<size &&this->compare(data[rightChildIndex],data[currentIndex])) {
            currentIndex = rightChildIndex;
        }
        if (currentIndex==index)
            break;
        std::swap(data[currentIndex],data[index]);
        index = currentIndex;

    }
}

template<class T, class Compare>
BinaryHeap<T, Compare>::BinaryHeap(Compare compare_) :compare(compare_){}

template<class T, class Compare>
BinaryHeap<T, Compare>::BinaryHeap( TreeIterator<T>& iterator_,Compare compare_):compare(compare_) {
    while (iterator_.hasNext()) {
        this->BinaryHeap<T, Compare>::push(iterator_.next());
    }
}



template<class T,class Compare>
bool BinaryHeap<T,Compare>::empty() const {
    return data.empty();
}

template<class T,class Compare>
std::size_t BinaryHeap<T,Compare>::size() const {
    return data.size();
}

template<class T,class Compare>
std::size_t BinaryHeap<T,Compare>::depth() const {
    return calcDepth(data.size());
}

template<class T,class Compare>
void BinaryHeap<T,Compare>::push(const T &element)  {
    data.push_back(element);
    heapifyUp(data.size()-1);
}

template<class T,class Compare>
void BinaryHeap<T,Compare>::pop()  {
    if (empty())
        throw std::runtime_error("优先级队列为空");
    std::swap(data[0],data.back());
    data.pop_back();
    heapifyDown(0);
}

template<class T,class Compare>
const T & BinaryHeap<T,Compare>::top() const {
    if (empty())
        throw std::runtime_error("优先级队列为空");
    return data[0];
}

template<class T,class Compare>
void BinaryHeap<T,Compare>::clear() {
    data.clear();
}

template<class T,class Compare>
auto BinaryHeap<T,Compare>::begin() const {
    return data.begin();
}

template<class T,class Compare>
auto BinaryHeap<T,Compare>::end() const{
    return data.end();
}


// template<class T>
// class MaxBinaryHeap:public BinaryHeap<T> {
// public:
//     bool compare(const T &a, const T &b) const override;
// };
//
// //最大堆
// template<class T>
// bool MaxBinaryHeap<T>::compare(const T &a, const T &b) const {
//     return a>b;
// }

template<class T>
using MinBinaryHeap=BinaryHeap<T,std::less<T>>;

template<class T>
using MaxBinaryHeap=BinaryHeap<T,std::greater<T>>;

// //最小堆
// template<class T>
// class MinBinaryHeap:public BinaryHeap<T> {
//
// public:
//     bool compare(const T &a, const T &b) const override;
// };
//
// template<class T>
// bool MinBinaryHeap<T>::compare(const T &a, const T &b) const {
//     return a<b;
// }

#endif //STUDYDATASTRUCT_BINARYHEAP_H
