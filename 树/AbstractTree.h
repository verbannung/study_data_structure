//
// Created by Ko-chieh Yin on 10/5/25.
//

#ifndef STUDYDATASTRUCT_ABSTRACTTREE_H
#define STUDYDATASTRUCT_ABSTRACTTREE_H
#include <cstddef>
#include <functional>

template <class T>
class AbstractTreeNode {
public:
    virtual ~AbstractTreeNode() = default;


    virtual const T& getElement() const = 0;
    virtual T& getElement() = 0;


    virtual AbstractTreeNode<T>* getParent() const = 0;
    virtual std::vector<AbstractTreeNode<T>*> getChildren() const = 0;
    [[nodiscard]] virtual bool hasChildren() const = 0;
};


template <class T, class NodeType>
class AbstractTree {
public:
    virtual ~AbstractTree() = default;

    // ---------- 基本性质 ----------
    [[nodiscard]] virtual bool empty() const = 0;
    [[nodiscard]] virtual std::size_t size() const = 0;
    [[nodiscard]] virtual std::size_t depth() const = 0;

    // ---------- 结构访问 ----------
    [[nodiscard]] virtual const NodeType* getRoot() const = 0;
    [[nodiscard]] virtual NodeType* getRoot() = 0;

    // ---------- 遍历 ----------
    virtual void preOrder(const std::function<void(const T&)>& visit) const = 0;
    virtual void postOrder(const std::function<void(const T&)>& visit) const = 0;
    virtual void levelOrder(const std::function<void(const T&)>& visit) const = 0;
};

#endif //STUDYDATASTRUCT_ABSTRACTTREE_H