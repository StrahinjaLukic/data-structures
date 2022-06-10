//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>
#include <data-structures/binary-search-tree/bt_update_strategies.hpp>

#include <gtest/gtest.h>

#include <string>

namespace
{
using KeyType = int;
using ValueType = std::string;
}  // namespace

TEST(NodeInsertionTest, InsertNodesLeftAndRight)
{
    using UpdateStrategy = RejectUpdates<KeyType, ValueType>;
    const auto node_maker = [](KeyType key, ValueType value) {
        return MakeBSTNode<UpdateStrategy>(key, value);
    };

    auto root = node_maker(0, std::string("root"));

    const auto right_insertion = root->Insert(node_maker(1, std::string("right")));
    EXPECT_TRUE(right_insertion.second);
    ASSERT_TRUE(right_insertion.first);
    EXPECT_EQ(1, right_insertion.first->Key());
    EXPECT_EQ("right", right_insertion.first->Value());

    const auto left_insertion = root->Insert(node_maker(-1, std::string("left")));
    EXPECT_TRUE(left_insertion.second);
    ASSERT_TRUE(left_insertion.first);
    EXPECT_EQ(-1, left_insertion.first->Key());
    EXPECT_EQ("left", left_insertion.first->Value());
}

TEST(NodeInsertionTest, UpdateStrategyReject_InsertingExistingNodeFails)
{
    using UpdateStrategy = RejectUpdates<KeyType, ValueType>;
    const auto node_maker = [](KeyType key, ValueType value) {
        return MakeBSTNode<UpdateStrategy>(key, value);
    };

    auto root = node_maker(0, std::string("root"));
    root->Insert(node_maker(1, std::string("right")));

    const auto root_overwrite = root->Insert(node_maker(0, std::string("uproot")));
    EXPECT_FALSE(root_overwrite.second);
    ASSERT_TRUE(root_overwrite.first);
    EXPECT_EQ("root", root_overwrite.first->Value());

    const auto right_overwrite = root->Insert(node_maker(1, std::string("outright")));
    EXPECT_FALSE(right_overwrite.second);
    ASSERT_TRUE(right_overwrite.first);
    EXPECT_EQ("right", right_overwrite.first->Value());
}

TEST(NodeInsertionTest, UpdateStrategyAccept_InsertingExistingNodeSucceeds)
{
    using UpdateStrategy = AcceptUpdates<KeyType, ValueType>;
    const auto node_maker = [](KeyType key, ValueType value) {
        return MakeBSTNode<UpdateStrategy>(key, value);
    };

    auto root = node_maker(0, std::string("root"));
    root->Insert(node_maker(1, std::string("right")));

    const auto root_overwrite = root->Insert(node_maker(0, std::string("uproot")));
    EXPECT_TRUE(root_overwrite.second);
    ASSERT_TRUE(root_overwrite.first);
    EXPECT_EQ("uproot", root_overwrite.first->Value());
    EXPECT_EQ(root, root_overwrite.first);
    EXPECT_TRUE(root_overwrite.first->Find(1));

    const auto right_overwrite = root->Insert(node_maker(1, std::string("outright")));
    EXPECT_TRUE(right_overwrite.second);
    ASSERT_TRUE(right_overwrite.first);
    EXPECT_EQ("outright", right_overwrite.first->Value());
    auto replaced_node = root->Find(1);
    ASSERT_TRUE(replaced_node);
    EXPECT_EQ("outright", replaced_node->Value());
}

TEST(NodeInsertionTest, InsertingNullNodeFails)
{
    using UpdateStrategy = RejectUpdates<KeyType, ValueType>;
    const auto node_maker = [](KeyType key, ValueType value) {
        return MakeBSTNode<UpdateStrategy>(key, value);
    };

    auto root = node_maker(0, std::string("root"));
    root->Insert(node_maker(1, std::string("right")));

    const auto null_insert = root->Insert(nullptr);
    EXPECT_FALSE(null_insert.second);
    EXPECT_FALSE(null_insert.first);
}
