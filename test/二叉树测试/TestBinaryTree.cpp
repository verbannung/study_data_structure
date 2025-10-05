//
// Created by Ko-chieh Yin on 10/4/25.
//

//
// Created by Ko-chieh Yin on 10/4/25.
//

#include "LinkedBinaryTree.h"
#include "../../树/BinaryTree.h"
#include "gtest/gtest.h"

class TestBinaryTree : public ::testing::Test {
protected:
    std::unique_ptr<LinkedBinaryTree<int>> tree;

    void SetUp() override {
        // 构造测试树：
        //          1
        //         / \
        //        2   3
        //       / \   \
        //      4   5   6

        auto root = std::make_unique<BinaryTreeNode<int>>(1);

        root->setLeft(std::make_unique<BinaryTreeNode<int>>(2));
        root->setRight(std::make_unique<BinaryTreeNode<int>>(3));

        root->getLeft()->setLeft(std::make_unique<BinaryTreeNode<int>>(4));
        root->getLeft()->setRight(std::make_unique<BinaryTreeNode<int>>(5));
        root->getRight()->setRight(std::make_unique<BinaryTreeNode<int>>(6));

        tree = std::make_unique<LinkedBinaryTree<int>>(std::move(root));
    }
};




// ------------------ 前序遍历 ------------------
TEST_F(TestBinaryTree, preOrder) {
    std::ostringstream buffer;
    auto visit = [&buffer](const int& value) {
        buffer << value << ' ';
    };

    tree->preOrder(visit);

    EXPECT_EQ(buffer.str(), "1 2 4 5 3 6 ");
}

// ------------------ 中序遍历 ------------------
TEST_F(TestBinaryTree, inOrder) {
    std::ostringstream buffer;
    tree->inOrder([&buffer](const int& v) {
        buffer << v << ' ';
    });
    EXPECT_EQ(buffer.str(), "4 2 5 1 3 6 ");
}

// ------------------ 后序遍历 ------------------
TEST_F(TestBinaryTree, postOrder) {
    std::ostringstream buffer;
    tree->postOrder([&buffer](const int& v) {
        buffer << v << ' ';
    });
    EXPECT_EQ(buffer.str(), "4 5 2 6 3 1 ");
}

// ------------------ 层序遍历 ------------------
TEST_F(TestBinaryTree, levelOrder) {
    std::ostringstream buffer;
    tree->levelOrder([&buffer](const int& v) {
        buffer << v << ' ';
    });
    EXPECT_EQ(buffer.str(), "1 2 3 4 5 6 ");
}

// ------------------ 深度与节点数 ------------------
TEST_F(TestBinaryTree, testTreeDepth) {
    EXPECT_EQ(tree->depth(), 3);
}

TEST_F(TestBinaryTree, testTreeSize) {
    EXPECT_EQ(tree->size(), 6);
}

