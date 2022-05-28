//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include <gtest/gtest.h>

#include <string>
#include <map>

namespace {
    template<typename TKey, typename TValue>
    typename BSTNode<TKey, TValue>::NodePtr
    MakeTree(const std::map<TKey, TValue> &key_values) {
        if (key_values.empty()) {
            return nullptr;
        }

        auto root = MakeBSTNode(key_values.begin()->first, key_values.begin()->second);

        for (auto it = std::next(key_values.begin()); it != key_values.end(); ++it) {
            root->Insert(MakeBSTNode(it->first, it->second));
        }

        return root;
    }
}

TEST(BSTNodeTest, InsertNodesLeftAndRight) {
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

TEST(BSTNodeTest, AttemptInsertingExistingNode) {
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

TEST(BSTNodeTest, AttemptInsertingNullNode) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeBSTNode(0, std::string("root"));
    root->Insert(MakeBSTNode(1, std::string("right")));

    const auto null_insert = root->Insert(nullptr);
    EXPECT_FALSE(null_insert.second);
    EXPECT_FALSE(null_insert.first);
}

TEST(BSTNodeTest, FindSelf) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeBSTNode(0, std::string("root"));

    const auto find_root = root->Find(root->Key());
    ASSERT_TRUE(find_root);
    ASSERT_EQ(root->Key(), find_root->Key());
    ASSERT_EQ(root->Value(), find_root->Value());
}

TEST(BSTNodeTest, FindExistingNodes) {
    using Node = BSTNode<int, std::string>;

    const std::map<int, std::string> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    for (const auto &key_value : input) {
        const auto found = root->Find(key_value.first);
        ASSERT_TRUE(found);
        EXPECT_EQ(key_value.first, found->Key());
        EXPECT_EQ(key_value.second, found->Value());
    }
}

TEST(BSTNodeTest, FindMissingNodes) {
    using Node = BSTNode<int, std::string>;

    const std::map<int, std::string> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    EXPECT_FALSE(root->Find(2));
}
