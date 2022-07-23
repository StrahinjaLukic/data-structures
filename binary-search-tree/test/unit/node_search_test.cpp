//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include "test_helpers.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace
{
template <typename... TArgs>
class DummyUpdateStrategy
{
    using Node = BSTNode<TArgs..., DummyUpdateStrategy<TArgs...>>;
    using NodePtr = typename Node::NodePtr;

public:
    std::pair<NodePtr, bool> operator()(Node& /* this_node */, Node&& /* new_node */)
    {
        return {nullptr, false};
    }
};

using KeyType = int;
using ValueType = std::string;
using UpdateStrategy = DummyUpdateStrategy<KeyType, ValueType>;
}  // namespace

TEST(NodeSearchTest, FindSelf)
{
    auto root = MakeBSTNode<UpdateStrategy>(0, std::string("root"));

    const auto find_root = root->Find(root->Key());
    ASSERT_TRUE(find_root);
    ASSERT_EQ(root->Key(), find_root->Key());
    ASSERT_EQ(root->Value(), find_root->Value());
}

TEST(NodeSearchTest, FindExistingNodes)
{
    const std::vector<std::pair<int, std::string>> input = {
        {0, "root"}, {-1, "left"}, {1, "right"}, {3, "three"}};

    const auto root = MakeTree<UpdateStrategy>(input);

    for (const auto& key_value : input)
    {
        const auto found = root->Find(key_value.first);
        ASSERT_TRUE(found);
        EXPECT_EQ(key_value.first, found->Key());
        EXPECT_EQ(key_value.second, found->Value());
    }
}

TEST(NodeSearchTest, FindMissingNodes)
{
    const std::vector<std::pair<int, std::string>> input = {
        {0, "root"}, {-1, "left"}, {1, "right"}, {3, "three"}};

    const auto root = MakeTree<UpdateStrategy>(input);

    EXPECT_FALSE(root->Find(2));
}
