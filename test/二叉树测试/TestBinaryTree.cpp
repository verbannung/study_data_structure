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





TEST_F(TestBinaryTree, preOrder) {
    std::ostringstream buffer;
    auto visit = [&buffer](const int& value) {
        buffer << value << ' ';
    };

    tree->preOrder(visit);

    EXPECT_EQ(buffer.str(), "1 2 4 5 3 6 ");
}


TEST_F(TestBinaryTree, inOrder) {
    std::ostringstream buffer;
    tree->inOrder([&buffer](const int& v) {
        buffer << v << ' ';
    });
    EXPECT_EQ(buffer.str(), "4 2 5 1 3 6 ");
}


TEST_F(TestBinaryTree, postOrder) {
    std::ostringstream buffer;
    tree->postOrder([&buffer](const int& v) {
        buffer << v << ' ';
    });
    EXPECT_EQ(buffer.str(), "4 5 2 6 3 1 ");
}


TEST_F(TestBinaryTree, levelOrder) {
    std::ostringstream buffer;
    tree->levelOrder([&buffer](const int& v) {
        buffer << v << ' ';
    });
    EXPECT_EQ(buffer.str(), "1 2 3 4 5 6 ");
}


TEST_F(TestBinaryTree, testTreeDepth) {
    EXPECT_EQ(tree->depth(), 3);
}

TEST_F(TestBinaryTree, testTreeSize) {
    EXPECT_EQ(tree->size(), 6);
}

TEST_F(TestBinaryTree, testClone) {
    auto clone = tree->clone();
    EXPECT_EQ(tree->size(), 6);
    EXPECT_EQ(tree->depth(), 3);

    auto linked_binary_tree = std::make_unique<LinkedBinaryTree<int>>();
    auto clone_linked_binary_tree = linked_binary_tree->clone();
    EXPECT_EQ(clone_linked_binary_tree->size(), 0);
    EXPECT_EQ(clone_linked_binary_tree->depth(), 0);
}

TEST_F(TestBinaryTree, testIterator) {
    auto iterator = tree->iterator();
    EXPECT_EQ(iterator->next(), 4);
    EXPECT_EQ(iterator->next(), 2);
    EXPECT_EQ(iterator->next(), 5);
    EXPECT_EQ(iterator->next(), 1);
    EXPECT_EQ(iterator->next(), 3);
    EXPECT_EQ(iterator->next(), 6);
    EXPECT_FALSE(iterator->hasNext());
    EXPECT_ANY_THROW(iterator->next());

    auto iterator2 = tree->iterator(TraversalOrder::LevelOrder);
    EXPECT_EQ(iterator2->next(), 1);
    EXPECT_EQ(iterator2->next(), 2);
    EXPECT_EQ(iterator2->next(), 3);
    EXPECT_EQ(iterator2->next(), 4);
    EXPECT_EQ(iterator2->next(), 5);
    EXPECT_EQ(iterator2->next(), 6);
    EXPECT_FALSE(iterator2->hasNext());
    EXPECT_ANY_THROW(iterator2->next());

    auto iterator3 = tree->iterator(TraversalOrder::PostOrder);
    EXPECT_EQ(iterator3->next(), 4);
    EXPECT_EQ(iterator3->next(), 5);
    EXPECT_EQ(iterator3->next(), 2);
    EXPECT_EQ(iterator3->next(), 6);
    EXPECT_EQ(iterator3->next(), 3);
    EXPECT_EQ(iterator3->next(), 1);
    EXPECT_FALSE(iterator3->hasNext());
    EXPECT_ANY_THROW(iterator3->next());

    auto iterator4 = tree->iterator(TraversalOrder::PreOrder);
    EXPECT_EQ(iterator4->next(), 1);
    EXPECT_EQ(iterator4->next(), 2);
    EXPECT_EQ(iterator4->next(), 4);
    EXPECT_EQ(iterator4->next(), 5);
    EXPECT_EQ(iterator4->next(), 3);
    EXPECT_EQ(iterator4->next(), 6);
    EXPECT_FALSE(iterator4->hasNext());
    EXPECT_ANY_THROW(iterator4->next());
}


