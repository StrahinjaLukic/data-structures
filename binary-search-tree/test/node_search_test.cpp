//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include "test_helpers.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(NodeSearchTest, FindSelf) {
    using Node = BSTNode<int, std::string>;

    auto root = MakeBSTNode(0, std::string("root"));

    const auto find_root = root->Find(root->Key());
    ASSERT_TRUE(find_root);
    ASSERT_EQ(root->Key(), find_root->Key());
    ASSERT_EQ(root->Value(), find_root->Value());
}

TEST(NodeSearchTest, FindExistingNodes) {
    using Node = BSTNode<int, std::string>;

    const std::vector<std::pair<int, std::string>> input = {
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

TEST(NodeSearchTest, FindMissingNodes) {
    using Node = BSTNode<int, std::string>;

    const std::vector<std::pair<int, std::string>> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    EXPECT_FALSE(root->Find(2));
}
