//
// Created by Ko-chieh Yin on 10/4/25.
//

#ifndef STUDYDATASTRUCT_BINARYTREE_H
#define STUDYDATASTRUCT_BINARYTREE_H
#include <cstddef>
#include <memory>

#include "AbstractTree.h"
#include "TreeIterator.h"

template <class T, class NodeType>
class BinaryTreeNodeBase : public AbstractTreeNode<T> {
protected:
    T element;
    NodeType* parent = nullptr;
    std::unique_ptr<NodeType> left;
    std::unique_ptr<NodeType> right;

public:
    explicit BinaryTreeNodeBase(const T& value) : element(value) {}

    BinaryTreeNodeBase(const T& value,
                       std::unique_ptr<NodeType> leftNode,
                       std::unique_ptr<NodeType> rightNode)
        : element(value),
          left(std::move(leftNode)),
          right(std::move(rightNode)) {
        if (left) left->parent = static_cast<NodeType*>(this);
        if (right) right->parent = static_cast<NodeType*>(this);
    }

    // 通用访问器
    const T& getElement() const override { return element; }
    T& getElement() override { return element; }

    [[nodiscard]] NodeType* getLeft() const { return left.get(); }
    [[nodiscard]] NodeType* getRight() const { return right.get(); }

    void setLeft(std::unique_ptr<NodeType> leftNode) {
        if (leftNode) leftNode->parent = static_cast<NodeType*>(this);
        left = std::move(leftNode);
    }

    void setRight(std::unique_ptr<NodeType> rightNode) {
        if (rightNode) rightNode->parent = static_cast<NodeType*>(this);
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

    [[nodiscard]] bool hasChildren() const override { return left || right; }

    std::unique_ptr<NodeType> clone() const {
        auto newNode = std::make_unique<NodeType>(element);
        if (left) {
            newNode->left = left->clone();
            newNode->left->parent = newNode.get();
        }
        if (right) {
            newNode->right = right->clone();
            newNode->right->parent = newNode.get();
        }
        return newNode;
    }
};

template <class T>
class BinaryTreeNode : public BinaryTreeNodeBase<T, BinaryTreeNode<T>> {
public:
    using Base = BinaryTreeNodeBase<T, BinaryTreeNode<T>>;
    using Base::Base;
};

// template <class T>
// class BinaryTreeNode : public AbstractTreeNode<T> {
// protected:
//     T element;
//     BinaryTreeNode<T>* parent = nullptr; //不拥有所有权
//     std::unique_ptr<BinaryTreeNode<T>> left;
//     std::unique_ptr<BinaryTreeNode<T>> right;
//
// public:
//     explicit BinaryTreeNode(const T& value) : element(value) {}
//
//     BinaryTreeNode(const T& value,
//                    std::unique_ptr<BinaryTreeNode<T>> leftNode,
//                    std::unique_ptr<BinaryTreeNode<T>> rightNode)
//         : element(value),
//           left(std::move(leftNode)),
//           right(std::move(rightNode)) {
//         if (left) left->parent = this;
//         if (right) right->parent = this;
//     }
//
//
//     const T& getElement() const override { return element; }
//     T& getElement() override { return element; }
//
//
//     [[nodiscard]] BinaryTreeNode<T>* getLeft() const { return left.get(); }
//     [[nodiscard]] BinaryTreeNode<T>* getRight() const { return right.get(); }
//
//     void setLeft(std::unique_ptr<BinaryTreeNode<T>> leftNode) {
//         if (leftNode) leftNode->parent = this;
//         left = std::move(leftNode);
//     }
//
//     void setRight(std::unique_ptr<BinaryTreeNode<T>> rightNode) {
//         if (rightNode) rightNode->parent = this;
//         right = std::move(rightNode);
//     }
//
//     [[nodiscard]] bool hasLeft() const { return static_cast<bool>(left); }
//     [[nodiscard]] bool hasRight() const { return static_cast<bool>(right); }
//
//
//     AbstractTreeNode<T>* getParent() const override { return parent; }
//
//     std::vector<AbstractTreeNode<T>*> getChildren() const override {
//         std::vector<AbstractTreeNode<T>*> result;
//         if (left) result.push_back(left.get());
//         if (right) result.push_back(right.get());
//         return result;
//     }
//
//     [[nodiscard]] bool hasChildren() const override {
//         return left || right;
//     }
//
//     std::unique_ptr<BinaryTreeNode<T>> clone() const {
//         auto newNode = std::make_unique<BinaryTreeNode<T>>(element);
//         if (left) {
//             newNode->left=left->clone();
//             newNode->left->parent=newNode.get();
//         }
//         if (right) {
//             newNode->right=right->clone();
//             newNode->right->parent=newNode.get();
//         }
//
//         return newNode;
//     }
// };

template <class T>
class BinaryTree : public AbstractTree{
public:
    ~BinaryTree() override = default;

    virtual void inOrder(const std::function<void(const T&)>& visit) const = 0;


    [[nodiscard]] virtual const BinaryTreeNode<T>* getRoot() const = 0;
    [[nodiscard]] virtual BinaryTreeNode<T>* getRoot() = 0;



    virtual void preOrder(const std::function<void(const T&)>& visit) const = 0;
    virtual void postOrder(const std::function<void(const T&)>& visit) const = 0;
    virtual void levelOrder(const std::function<void(const T&)>& visit) const = 0;
    virtual std::unique_ptr<BinaryTree<T>> clone() const=0;

    virtual std::unique_ptr<TreeIterator<T>> iterator( TraversalOrder order) const = 0;




};

#endif //STUDYDATASTRUCT_BINARYTREE_H