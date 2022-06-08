//
// Created by strahinja on 5/29/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include "test_helpers.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {
    enum class OperationType : bool {
        kInsert, kRemove
    };
    using KeyType = int;
    using ValueType = std::string;
    using Node = BSTNode<KeyType, ValueType>;

    struct Operation {
        OperationType type;
        KeyType key;
        ValueType value;
    };
}

struct IteratorTestData {
    std::vector<std::pair<KeyType, ValueType>> initial_input;
    std::vector<Operation> operations;
    std::vector<std::pair<KeyType, ValueType>> expected_output;
    std::string name;
};

class IteratorTest : public testing::TestWithParam<IteratorTestData> {
protected:
    static void PerformOperations(Node &root, const std::vector<Operation> &operations) {
        for (const auto &operation: operations) {
            if (operation.type == OperationType::kInsert) {
                root.Insert(MakeBSTNode(operation.key, operation.value));
            } else {
                root.Remove(operation.key);
            }
        }
    }
};

TEST_P(IteratorTest, VerifyOrder) {
    auto root = MakeTree(GetParam().initial_input);
    ASSERT_TRUE(root);
    PerformOperations(*root, GetParam().operations);
    auto it = root->Begin();

    for (const auto &expected : GetParam().expected_output) {
        ASSERT_FALSE(it == root->End());
        EXPECT_EQ(expected.first, (*it).Key());
        EXPECT_EQ(expected.second, (*it).Value());
        ++it;
        EXPECT_TRUE(root->Find(expected.first));
    }

    EXPECT_EQ(it, root->End());
}

INSTANTIATE_TEST_SUITE_P(OrderVerification, IteratorTest,
                         testing::Values(
                                 IteratorTestData{
                                         {{10, "ten"}, {11, "eleven"}, {5, "five"}},
                                         {{OperationType::kInsert, 6, "six"}, {OperationType::kRemove, 10, ""}},
                                         {{5, "five"}, {6, "six"}, {11, "eleven"}},
                                         "Simple"
                                 },
                                 IteratorTestData{
                                         {{10, "ten"}, {8, "eight"}, {15, "fifteen"}, {11, "eleven"}, {5, "five"}},
                                         {{OperationType::kInsert, 6, "six"}, {OperationType::kRemove, 10, ""},
                                          {OperationType::kRemove, 2, ""}, {OperationType::kInsert, 16, "sixteen"}},
                                         {{5, "five"}, {6, "six"}, {8, "eight"}, {11, "eleven"}, {15, "fifteen"},
                                          {16, "sixteen"}},
                                         "RemoveNonExisting"
                                 }
                         ),
                         [](const testing::TestParamInfo<IteratorTest::ParamType> &info) {
                             return info.param.name;
                         }
);
