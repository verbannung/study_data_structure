//
// Created by Ko-chieh Yin on 10/7/25.
//

#ifndef STUDYDATASTRUCT_TREEITERATOR_H
#define STUDYDATASTRUCT_TREEITERATOR_H
#include <functional>


template<class T>
class TreeIterator {
public:
    virtual ~TreeIterator()=default;

    virtual void traverse(const std::function<void(const T&)> &visit) =0;

    [[nodiscard]] virtual bool hasNext() const=0;
    virtual const T& next() =0;
};

enum class TraversalOrder {
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};



#endif //STUDYDATASTRUCT_TREEITERATOR_H