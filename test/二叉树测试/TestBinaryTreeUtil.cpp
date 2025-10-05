//
// Created by Ko-chieh Yin on 10/5/25.
//

#include "BinaryTree.h"
#include "BinaryTreeUtil.h"
#include "LinkedBinaryTree.h"
#include "gtest/gtest.h"
TEST(CompleteBinaryTreeTest, 是否完全二叉树1) {
    auto root = std::make_unique<BinaryTreeNode<int>>(1);

    root->setLeft(std::make_unique<BinaryTreeNode<int>>(2));
    root->setRight(std::make_unique<BinaryTreeNode<int>>(3));

    root->getLeft()->setLeft(std::make_unique<BinaryTreeNode<int>>(4));
    root->getLeft()->setRight(std::make_unique<BinaryTreeNode<int>>(5));
    root->getRight()->setRight(std::make_unique<BinaryTreeNode<int>>(6));


    EXPECT_FALSE(isCompleteTree(root.get()));
}

TEST(CompleteBinaryTreeTest, 是否完全二叉树2) {
    auto root = std::make_unique<BinaryTreeNode<int>>(1);

    root->setLeft(std::make_unique<BinaryTreeNode<int>>(2));
    root->setRight(std::make_unique<BinaryTreeNode<int>>(3));

    root->getLeft()->setLeft(std::make_unique<BinaryTreeNode<int>>(4));
    root->getLeft()->setRight(std::make_unique<BinaryTreeNode<int>>(5));
    root->getRight()->setLeft(std::make_unique<BinaryTreeNode<int>>(7));
    root->getRight()->setRight(std::make_unique<BinaryTreeNode<int>>(6));


    EXPECT_TRUE(isCompleteTree(root.get()));
}

