//
// Created by strahinja on 5/26/22.
//

#ifndef BINARY_SEARCH_TREE_BST_NODE_HPP
#define BINARY_SEARCH_TREE_BST_NODE_HPP

#include <memory>

/**
 * Node of a binary search tree
 *
 * @tparam TKey key type
 * @tparam TValue value type
 */
template<typename TKey, typename TValue>
class BSTNode {
public:
    using NodeType = BSTNode<TKey, TValue>;

    BSTNode(TKey key, TValue value) :
            key_(key), value_(value) {}

    /**
     * Inserts new_node to the appropriate descendant leaf,
     * if the tree does not already contain a node with the same key
     *
     * @param new_node Node to insert
     * @return true if the new node was inserted into the appropriate descendant leaf, false otherwise
     */
    bool Insert(std::unique_ptr<NodeType> &&new_node);

    TKey Key() {
        return key_;
    }

    TValue Value() {
        return value_;
    }

private:
    TKey key_;
    TValue value_;

    std::unique_ptr<NodeType> left_;
    std::unique_ptr<NodeType> right_;
};

bool BSTNode<TKey, TValue>::Insert(std::unique_ptr<NodeType> &&new_node) {
    if (!new_node) {
        return false;
    }

    if(new_node->Key() == key_) {
        return false;
    }

    if (new_node->Key() < key_) {
        if (!left_) {
            left_.swap(new_node);
            return true;
        }
        return left_->Insert(std::move(new_node));
    }

    if(!right_) {
        right_.swap(new_node);
        return true;
    }
    return right_->Insert(std::move(new_node));
}

#endif //BINARY_SEARCH_TREE_BST_NODE_HPP
