//
// Created by strahinja on 5/27/22.
//

#include <data-structures/binary-search-tree/bst_node.hpp>

#include <map>

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
