//
// Created by Ko-chieh Yin on 10/4/25.
//

#ifndef STUDYDATASTRUCT_LINKEDBINARYTREE_H
#define STUDYDATASTRUCT_LINKEDBINARYTREE_H
#include <memory>
#include <queue>

#include "BinaryTree.h"
#include "BinaryTreeUtil.h"

template <class T>
class LinkedBinaryTree : public BinaryTree<T> {



public:
    LinkedBinaryTree() = default;
    explicit LinkedBinaryTree(std::unique_ptr<BinaryTreeNode<T>>&& _root)
        : root(std::move(_root)) {
        updateMeta();
    }

    [[nodiscard]] bool empty() const override { return !root; }
    [[nodiscard]] std::size_t size() const override { return treeSize; }
    [[nodiscard]] std::size_t depth() const override { return treeDepth; }

    [[nodiscard]] const BinaryTreeNode<T>* getRoot() const override { return root.get(); }
    [[nodiscard]] BinaryTreeNode<T>* getRoot() override { return root.get(); }


    void preOrder(const std::function<void(const T&)>& visit) const override {
        preOrderImpl(root.get(), visit);
    }

    void inOrder(const std::function<void(const T&)>& visit) const override {
        inOrderImpl(root.get(), visit);
    }

    void postOrder(const std::function<void(const T&)>& visit) const override {
        postOrderImpl(root.get(), visit);
    }

    void levelOrder(const std::function<void(const T&)>& visit) const override {
        if (!root) return;
        std::queue<BinaryTreeNode<T>*> q;
        q.push(root.get());
        while (!q.empty()) {
            auto* node = q.front();
            q.pop();
            visit(node->getElement());
            if (node->getLeft()) q.push(node->getLeft());
            if (node->getRight()) q.push(node->getRight());
        }
    }

    void setRoot(std::unique_ptr<BinaryTreeNode<T>> newRoot) {
        root = std::move(newRoot);
        updateMeta();
    }

private:
    std::unique_ptr<BinaryTreeNode<T>> root;
    std::size_t treeDepth = 0;
    std::size_t treeSize = 0;

    // static std::size_t calcDepth(const BinaryTreeNode<T>* node) {
    //     if (!node) return 0;
    //     return 1 + std::max(calcDepth(node->getLeft()), calcDepth(node->getRight()));
    // }

    // static std::size_t calcSize(const BinaryTreeNode<T>* node) {
    //     if (!node) return 0;
    //     return 1 + calcSize(node->getLeft()) + calcSize(node->getRight());
    // }


    void preOrderImpl(const BinaryTreeNode<T>* node, const std::function<void(const T&)>& visit) const {
        if (!node) return;
        visit(node->getElement());
        preOrderImpl(node->getLeft(), visit);
        preOrderImpl(node->getRight(), visit);
    }

    void inOrderImpl(const BinaryTreeNode<T>* node, const std::function<void(const T&)>& visit) const {
        if (!node) return;
        inOrderImpl(node->getLeft(), visit);
        visit(node->getElement());
        inOrderImpl(node->getRight(), visit);
    }

    void postOrderImpl(const BinaryTreeNode<T>* node, const std::function<void(const T&)>& visit) const {
        if (!node) return;
        postOrderImpl(node->getLeft(), visit);
        postOrderImpl(node->getRight(), visit);
        visit(node->getElement());
    }

    void updateMeta() {
        treeDepth = calcDepth(root.get());
        treeSize = calcSize(root.get());
    }


};


#endif //STUDYDATASTRUCT_LINKEDBINARYTREE_H