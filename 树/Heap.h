//
// Created by Ko-chieh Yin on 10/6/25.
//

#ifndef STUDYDATASTRUCT_HEAP_H
#define STUDYDATASTRUCT_HEAP_H
#include "AbstractTree.h"


template<class T>
class Heap : public AbstractTree{
public:
     ~Heap() override =default;

    virtual void push(const T& element)  = 0;  //插入元素
    virtual void pop()  = 0;   //删除堆顶元素
    virtual const T& top() const=0;  //获取堆顶元素
    virtual void clear()  = 0;  //清空堆

    // virtual bool compare(const T&a, const T&b) const =0;
};


#endif //STUDYDATASTRUCT_HEAP_H