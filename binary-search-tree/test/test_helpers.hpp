//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include <vector>
#include <utility>

template<typename TUpdateStrategy, typename TKey, typename TValue>
typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr
MakeTree(const std::vector<std::pair<TKey, TValue>> &key_values) {
    if (key_values.empty()) {
        return nullptr;
    }

    auto root = MakeBSTNode<TUpdateStrategy>(key_values.begin()->first, key_values.begin()->second);

    for (auto it = std::next(key_values.begin()); it != key_values.end(); ++it) {
        root->Insert(MakeBSTNode<TUpdateStrategy>(it->first, it->second));
    }

    return root;
}
