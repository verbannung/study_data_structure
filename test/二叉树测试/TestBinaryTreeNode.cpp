//
// Created by Ko-chieh Yin on 10/4/25.
//

#include "BinaryTree.h"
#include "gtest/gtest.h"

class TestBinaryTreeNode : public ::testing::Test {
protected:
    std::unique_ptr<BinaryTreeNode<int>> root;

    void SetUp() override {
        // 构造简单二叉树：
        //       1
        //      / \
        //     2   3
        auto left = std::make_unique<BinaryTreeNode<int>>(2);
        auto right = std::make_unique<BinaryTreeNode<int>>(3);
        root = std::make_unique<BinaryTreeNode<int>>(1);
        root->setLeft(std::move(left));
        root->setRight(std::move(right));
    }
};


TEST_F(TestBinaryTreeNode, 节点基本值) {
    EXPECT_EQ(root->getElement(), 1);
    EXPECT_EQ(root->getLeft()->getElement(), 2);
    EXPECT_EQ(root->getRight()->getElement(), 3);
}


TEST_F(TestBinaryTreeNode, 左右孩子存在性) {
    EXPECT_TRUE(root->hasLeft());
    EXPECT_TRUE(root->hasRight());
    EXPECT_FALSE(root->getLeft()->hasChildren());
    EXPECT_FALSE(root->getRight()->hasChildren());
}


TEST_F(TestBinaryTreeNode, 父子关系正确) {
    EXPECT_EQ(root->getLeft()->getParent(), root.get());
    EXPECT_EQ(root->getRight()->getParent(), root.get());
    EXPECT_EQ(root->getParent(), nullptr);
}

TEST_F(TestBinaryTreeNode, getChildren正确) {
    auto children = root->getChildren();
    ASSERT_EQ(children.size(), 2);
    EXPECT_EQ(children[0]->getElement(), 2);
    EXPECT_EQ(children[1]->getElement(), 3);
}