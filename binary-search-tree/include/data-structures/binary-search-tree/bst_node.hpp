//
// Created by strahinja on 5/26/22.
//

#ifndef BINARY_SEARCH_TREE_BST_NODE_HPP
#define BINARY_SEARCH_TREE_BST_NODE_HPP

#include <memory>
#include <utility>

/**
 * Node of a binary search tree
 *
 * @tparam TKey key type
 * @tparam TValue value type
 */
template<typename TKey, typename TValue>
class BSTNode : public std::enable_shared_from_this<BSTNode<TKey, TValue>> {
public:
    using NodeType = BSTNode<TKey, TValue>;
    using NodePtr = std::shared_ptr<NodeType>;

    BSTNode(TKey key, TValue value) :
            key_(key), value_(value) {}

    /**
     * Inserts new_node to the appropriate descendant leaf,
     * if the tree does not already contain a node with the same key.
     *
     * @param new_node Node to insert.
     * @return a pair consisting of an pointer and a boolean. The pointer points:
     *  - To the inserted element if the insertion took place.
     *  - To the element that prevented the insertion if tree already contains a node with the same key.
     *  - Nullptr if new_node is nullptr.
     *  The boolean is true if the new node was successfully inserted, false otherwise.
     */
    std::pair<NodePtr, bool> Insert(NodePtr new_node);

    /**
     * Searches for the node with the given key.
     *
     * @param key Key to search for.
     * @return NodePtr pointing to the requested node, or nullptr if the node with the requested key was not found.
     */
    NodePtr Find(TKey key);

    TKey Key() {
        return key_;
    }

    TValue Value() {
        return value_;
    }

private:
    TKey key_;
    TValue value_;

    NodePtr left_;
    NodePtr right_;
};

template<typename TKey, typename TValue>
std::pair<typename BSTNode<TKey, TValue>::NodePtr, bool>
BSTNode<TKey, TValue>::Insert(NodePtr new_node) {
    if (!new_node) {
        return {nullptr, false};
    }

    if(new_node->Key() == key_) {
        return {this->shared_from_this(), false};
    }

    if (new_node->Key() < key_) {
        if (!left_) {
            left_.swap(new_node);
            return {left_, true};
        }
        return left_->Insert(std::move(new_node));
    }

    if(!right_) {
        right_.swap(new_node);
        return {right_, true};
    }
    return right_->Insert(std::move(new_node));
}

template<typename TKey, typename TValue>
typename BSTNode<TKey, TValue>::NodePtr BSTNode<TKey, TValue>::Find(TKey key) {
    if (key == key_) {
        return this->shared_from_this();
    }

    if (key > key_) {
        return right_ ? right_->Find(key) : nullptr;
    }

    return left_ ? left_->Find(key) : nullptr;
}

#endif //BINARY_SEARCH_TREE_BST_NODE_HPP
