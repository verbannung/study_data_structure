//
// Created by Ko-chieh Yin on 10/4/25.
//

#ifndef STUDYDATASTRUCT_BINARYTREE_H
#define STUDYDATASTRUCT_BINARYTREE_H
#include <cstddef>
#include <memory>

#include "AbstractTree.h"

template <class T>
class BinaryTreeNode : public AbstractTreeNode<T> {
private:
    T element;
    BinaryTreeNode<T>* parent = nullptr;
    std::unique_ptr<BinaryTreeNode<T>> left;
    std::unique_ptr<BinaryTreeNode<T>> right;

public:
    explicit BinaryTreeNode(const T& value) : element(value) {}

    BinaryTreeNode(const T& value,
                   std::unique_ptr<BinaryTreeNode<T>> leftNode,
                   std::unique_ptr<BinaryTreeNode<T>> rightNode)
        : element(value),
          left(std::move(leftNode)),
          right(std::move(rightNode)) {}

    // 数据访问
    const T& getElement() const override { return element; }
    T& getElement() override { return element; }

    // 左右访问
    [[nodiscard]] BinaryTreeNode<T>* getLeft() const { return left.get(); }
    [[nodiscard]] BinaryTreeNode<T>* getRight() const { return right.get(); }

    void setLeft(std::unique_ptr<BinaryTreeNode<T>> leftNode) {
        if (leftNode) leftNode->parent = this;
        left = std::move(leftNode);
    }

    void setRight(std::unique_ptr<BinaryTreeNode<T>> rightNode) {
        if (rightNode) rightNode->parent = this;
        right = std::move(rightNode);
    }

    [[nodiscard]] bool hasLeft() const { return static_cast<bool>(left); }
    [[nodiscard]] bool hasRight() const { return static_cast<bool>(right); }


    AbstractTreeNode<T>* getParent() const override { return parent; }

    std::vector<AbstractTreeNode<T>*> getChildren() const override {
        std::vector<AbstractTreeNode<T>*> result;
        if (left) result.push_back(left.get());
        if (right) result.push_back(right.get());
        return result;
    }

    [[nodiscard]] bool hasChildren() const override {
        return left || right;
    }
};

template <class T>
class BinaryTree : public AbstractTree<T, BinaryTreeNode<T>> {
public:
    ~BinaryTree() override = default;

    virtual void inOrder(const std::function<void(const T&)>& visit) const = 0;

    [[nodiscard]] const BinaryTreeNode<T>* getRoot() const override = 0;

};

#endif //STUDYDATASTRUCT_BINARYTREE_H