//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include <gtest/gtest.h>

#include <string>
#include <memory>

namespace {
    template<typename TKey, typename TValue>
    typename BSTNode<TKey, TValue>::NodePtr MakeNode(TKey key, TValue value) {
        return std::make_shared<BSTNode<TKey, TValue>>(key, value);
    }
}

TEST(BSTNodeTest, InsertNodesLeftAndRight) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeNode(0, std::string("root"));

    const auto right_insertion = root->Insert(MakeNode(1, std::string("right")));
    EXPECT_TRUE(right_insertion.second);
    ASSERT_TRUE(right_insertion.first);
    EXPECT_EQ(1, right_insertion.first->Key());
    EXPECT_EQ("right", right_insertion.first->Value());

    const auto left_insertion = root->Insert(MakeNode(-1, std::string("left")));
    EXPECT_TRUE(left_insertion.second);
    ASSERT_TRUE(left_insertion.first);
    EXPECT_EQ(-1, left_insertion.first->Key());
    EXPECT_EQ("left", left_insertion.first->Value());
}

TEST(BSTNodeTest, AttemptInsertingExistingNode) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeNode(0, std::string("root"));
    root->Insert(MakeNode(1, std::string("right")));

    const auto root_overwrite = root->Insert(MakeNode(0, std::string("uproot")));
    EXPECT_FALSE(root_overwrite.second);
    ASSERT_TRUE(root_overwrite.first);
    EXPECT_EQ("root", root_overwrite.first->Value());

    const auto right_overwrite = root->Insert(MakeNode(1, std::string("outright")));
    EXPECT_FALSE(right_overwrite.second);
    ASSERT_TRUE(right_overwrite.first);
    EXPECT_EQ("right", right_overwrite.first->Value());
}

TEST(BSTNodeTest, AttemptInsertingNullNode) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeNode(0, std::string("root"));
    root->Insert(MakeNode(1, std::string("right")));

    const auto null_insert = root->Insert(nullptr);
    EXPECT_FALSE(null_insert.second);
    EXPECT_FALSE(null_insert.first);
}