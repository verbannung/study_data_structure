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

// ---------- 节点基本值 ----------
TEST_F(TestBinaryTreeNode, ElementValues) {
    EXPECT_EQ(root->getElement(), 1);
    EXPECT_EQ(root->getLeft()->getElement(), 2);
    EXPECT_EQ(root->getRight()->getElement(), 3);
}

// ---------- 左右孩子存在性 ----------
TEST_F(TestBinaryTreeNode, ChildrenExistence) {
    EXPECT_TRUE(root->hasLeft());
    EXPECT_TRUE(root->hasRight());
    EXPECT_FALSE(root->getLeft()->hasChildren());
    EXPECT_FALSE(root->getRight()->hasChildren());
}

// ---------- 父子关系正确 ----------
TEST_F(TestBinaryTreeNode, ParentLinks) {
    EXPECT_EQ(root->getLeft()->getParent(), root.get());
    EXPECT_EQ(root->getRight()->getParent(), root.get());
    EXPECT_EQ(root->getParent(), nullptr);
}

// ---------- getChildren() 正确 ----------
TEST_F(TestBinaryTreeNode, GetChildrenVector) {
    auto children = root->getChildren();
    ASSERT_EQ(children.size(), 2);
    EXPECT_EQ(children[0]->getElement(), 2);
    EXPECT_EQ(children[1]->getElement(), 3);
}