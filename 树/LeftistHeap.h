//
// Created by Ko-chieh Yin on 10/8/25.
//

#ifndef STUDYDATASTRUCT_LEFTISTHEAP_H
#define STUDYDATASTRUCT_LEFTISTHEAP_H

#include "BinaryHeap.h"
#include <algorithm>
#include <memory>
#include <stdexcept>

// 左偏树节点
template<class T>
class LeftistHeapNode : public BinaryTreeNodeBase<T, LeftistHeapNode<T>> {
    template<class U,class Compare>
    friend class LeftistHeap;
private:
    int s; // null-path length
public:
    explicit LeftistHeapNode(const T& _element)
        : BinaryTreeNodeBase<T, LeftistHeapNode<T>>(_element), s(0) {}

    LeftistHeapNode(const T& value,
                    std::unique_ptr<LeftistHeapNode<T>> leftNode,
                    std::unique_ptr<LeftistHeapNode<T>> rightNode)
        : BinaryTreeNodeBase<T, LeftistHeapNode<T>>(value, std::move(leftNode), std::move(rightNode))
    {
        int leftS  = BinaryTreeNodeBase<T,LeftistHeapNode<T>>::left  ? BinaryTreeNodeBase<T,LeftistHeapNode<T>>::left->getS()  : -1;
        int rightS = BinaryTreeNodeBase<T,LeftistHeapNode<T>>::right ? BinaryTreeNodeBase<T,LeftistHeapNode<T>>::right->getS() : -1;
        s = std::min(leftS, rightS) + 1;
    }

    [[nodiscard]] int getS() const { return s; }
    void setS(const int _s) { s = _s; }

    void swapChildren() {
        std::swap(this->left, this->right);
    }


};

// 左偏树堆
template<class T, class Compare = std::less<T>>
class LeftistHeap : public BinaryHeap<T> {
private:
    std::unique_ptr<LeftistHeapNode<T>> root;
    std::size_t count = 0;
    Compare compare;

    static int getS(const std::unique_ptr<LeftistHeapNode<T>>& node) {
        return node ? node->getS() : -1;
    }

    // merge核心递归逻辑
    std::unique_ptr<LeftistHeapNode<T>> merge_(
        std::unique_ptr<LeftistHeapNode<T>> h1,
        std::unique_ptr<LeftistHeapNode<T>> h2
       )
    {
        if (!h1) return std::move(h2);
        if (!h2) return std::move(h1);


        if (compare(h2->element, h1->element))
            std::swap(h1, h2);

        h1->right=merge_(std::move(h1->right),std::move(h2));

        if (getS(h1->left)<getS(h1->right))
            h1->swapChildren();

        if (h1->left)  h1->left->parent  = h1.get();
        if (h2->right) h2->right->parent = h2.get();
        h1->setS(getS(h1->right)+1);
        return h1;

    }

    static std::size_t height(const LeftistHeapNode<T>* node) {
        if (!node) return 0;
        return 1 + std::max(height(node->left.get()), height(node->right.get()));
    }

public:
    LeftistHeap()=default;
    ~LeftistHeap() override = default;

    [[nodiscard]] bool empty() const override { return !root; }
    [[nodiscard]] std::size_t size() const override { return count; }
    [[nodiscard]] std::size_t depth() const override {
        return height(root.get());
    }

    void clear() override {
        root.reset();
        count = 0;
    }

    const T& top() const override {
        if (!root) throw std::runtime_error("Heap is empty");
        return root->element;
    }

    void push(const T& element) override {
        auto node = std::make_unique<::LeftistHeapNode<T>>(element);
        root = merge_(std::move(root), std::move(node));
        ++count;
    }

    void pop() override {
        if (!root) throw std::runtime_error("Heap is empty");
        root = merge_(std::move(root->left), std::move(root->right));
        --count;
    }


    void merge(LeftistHeap<T>& other) {
        root = merge_(std::move(root), std::move(other.root));
        count += other.count;
        other.count = 0;
    }
};

#endif //STUDYDATASTRUCT_LEFTISTHEAP_H