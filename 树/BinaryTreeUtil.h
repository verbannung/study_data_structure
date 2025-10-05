//
// Created by Ko-chieh Yin on 10/5/25.
//

#ifndef STUDYDATASTRUCT_BINARYTREEUTIL_H
#define STUDYDATASTRUCT_BINARYTREEUTIL_H
#include <queue>

#include "BinaryTree.h"

template<class T>
//广度优先算法
inline bool isCompleteTree(const BinaryTreeNode<T> *root) {
    if (!root) return true;
    std::queue<const BinaryTreeNode<T> *> q;
    q.push(root);
    bool encounteredNull = false;
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        if (!front) {
            encounteredNull = true;
        }else {
            if (encounteredNull) return false;
            q.push(front->getLeft());
            q.push(front->getRight());
        }

    }


    return true;
}

template<class T>
inline std::size_t calcDepth(const BinaryTreeNode<T>* node) {
    if (!node) return 0;
    return 1 + std::max(calcDepth(node->getLeft()), calcDepth(node->getRight()));
}

template<class T>
inline  std::size_t calcSize(const BinaryTreeNode<T>* node) {
    if (!node) return 0;
    return 1 + calcSize(node->getLeft()) + calcSize(node->getRight());
}



#endif //STUDYDATASTRUCT_BINARYTREEUTIL_H