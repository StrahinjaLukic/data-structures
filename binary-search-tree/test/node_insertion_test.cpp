//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include <gtest/gtest.h>

#include <string>

TEST(NodeInsertionTest, InsertNodesLeftAndRight) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeBSTNode(0, std::string("root"));

    const auto right_insertion = root->Insert(MakeBSTNode(1, std::string("right")));
    EXPECT_TRUE(right_insertion.second);
    ASSERT_TRUE(right_insertion.first);
    EXPECT_EQ(1, right_insertion.first->Key());
    EXPECT_EQ("right", right_insertion.first->Value());

    const auto left_insertion = root->Insert(MakeBSTNode(-1, std::string("left")));
    EXPECT_TRUE(left_insertion.second);
    ASSERT_TRUE(left_insertion.first);
    EXPECT_EQ(-1, left_insertion.first->Key());
    EXPECT_EQ("left", left_insertion.first->Value());
}

TEST(NodeInsertionTest, AttemptInsertingExistingNode) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeBSTNode(0, std::string("root"));
    root->Insert(MakeBSTNode(1, std::string("right")));

    const auto root_overwrite = root->Insert(MakeBSTNode(0, std::string("uproot")));
    EXPECT_FALSE(root_overwrite.second);
    ASSERT_TRUE(root_overwrite.first);
    EXPECT_EQ("root", root_overwrite.first->Value());

    const auto right_overwrite = root->Insert(MakeBSTNode(1, std::string("outright")));
    EXPECT_FALSE(right_overwrite.second);
    ASSERT_TRUE(right_overwrite.first);
    EXPECT_EQ("right", right_overwrite.first->Value());
}

TEST(NodeInsertionTest, AttemptInsertingNullNode) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeBSTNode(0, std::string("root"));
    root->Insert(MakeBSTNode(1, std::string("right")));

    const auto null_insert = root->Insert(nullptr);
    EXPECT_FALSE(null_insert.second);
    EXPECT_FALSE(null_insert.first);
}
