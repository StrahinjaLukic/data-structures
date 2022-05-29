//
// Created by strahinja on 5/28/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include "test_helpers.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(RemoveNextTest, NextIsLeaf) {
    using Node = BSTNode<int, std::string>;

    const std::vector<std::pair<int, std::string>> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    const auto removed = root->RemoveNext(Direction::kLeft);
    ASSERT_TRUE(removed);
    EXPECT_EQ(-1, removed->Key());
    EXPECT_EQ("left", removed->Value());

    for (const auto &key_value : input) {
        if (key_value.first == removed->Key()) {
            continue;
        }

        const auto found = root->Find(key_value.first);
        ASSERT_TRUE(found);
        EXPECT_EQ(key_value.second, found->Value());
    }
}

TEST(RemoveNextTest, NextHasPosterity) {
    using Node = BSTNode<int, std::string>;

    const std::vector<std::pair<int, std::string>> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    const auto removed = root->RemoveNext(Direction::kRight);
    ASSERT_TRUE(removed);
    EXPECT_EQ(1, removed->Key());
    EXPECT_EQ("right", removed->Value());

    for (const auto &key_value : input) {
        if (key_value.first == removed->Key()) {
            continue;
        }

        const auto found = root->Find(key_value.first);
        ASSERT_TRUE(found);
        EXPECT_EQ(key_value.second, found->Value());
    }
}

TEST(NodeDeletionTest, DeleteExistingNodes) {
    using Node = BSTNode<int, std::string>;

    const std::vector<std::pair<int, std::string>> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    for (auto it = std::next(input.begin()); it != input.end(); ++it) {
        const auto deletion_result = root->Remove(it->first);
        ASSERT_TRUE(deletion_result);
        EXPECT_EQ(it->first, deletion_result->Key());
        EXPECT_EQ(it->second, deletion_result->Value());
        EXPECT_FALSE(root->Find(it->first));
    }
}

TEST(NodeDeletionTest, DeleteNonExistingNode) {
    using Node = BSTNode<int, std::string>;

    const std::vector<std::pair<int, std::string>> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    EXPECT_FALSE(root->Remove(2));
}

TEST(NodeDeletionTest, DeleteRootNode_AnotherNodeBecomesRoot) {
    using Node = BSTNode<int, std::string>;

    const std::vector<std::pair<int, std::string>> input = {
            {0,  "root"},
            {-1, "left"},
            {1,  "right"},
            {3,  "three"}
    };

    const auto root = MakeTree(input);

    const auto deletion_result = root->Remove(0);
    ASSERT_TRUE(deletion_result);
    EXPECT_EQ(0, deletion_result->Key());
    EXPECT_EQ("root", deletion_result->Value());

    ASSERT_TRUE(root);
    EXPECT_TRUE(root->Find(-1));
    EXPECT_TRUE(root->Find(1));
    EXPECT_TRUE(root->Find(3));
}
