//
// Created by strahinja on 5/26/22.
//

#ifndef BINARY_SEARCH_TREE_BST_NODE_HPP
#define BINARY_SEARCH_TREE_BST_NODE_HPP

#include "bt_concepts.hpp"
#include "bt_iterator.hpp"

#include <concepts>
#include <memory>
#include <utility>

/**
 * Direction of a descendant of a binary tree node.
 */
enum class Direction : bool
{
    kLeft,
    kRight
};

/**
 * Node of a binary search tree
 *
 * @tparam TKey key type
 * @tparam TValue value type
 */
template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
class BSTNode : public std::enable_shared_from_this<BSTNode<TKey, TValue, TUpdateStrategy>>
{
public:
    using NodeType = BSTNode<TKey, TValue, TUpdateStrategy>;
    using NodePtr = std::shared_ptr<NodeType>;
    using ConstNodePtr = std::shared_ptr<const NodeType>;
    using ConstIterator = BinaryTreeConstIterator<TKey, TValue, TUpdateStrategy>;

    BSTNode(TKey key, TValue value) : key_(key), value_(value) {}

    /**
     * Inserts new_node to the appropriate descendant leaf,
     * if the tree does not already contain a node with the same key.
     *
     * @param new_node Node to insert.
     * @return a pair consisting of an pointer and a boolean. The pointer points:
     *  - To the inserted element if the insertion took place.
     *  - To the element that prevented the insertion if tree already contains a node with the same
     * key.
     *  - Nullptr if new_node is nullptr.
     *  The boolean is true if the new node was successfully inserted, false otherwise.
     */
    std::pair<NodePtr, bool> Insert(
        NodePtr new_node) requires CallableWithUpdateSignature<TUpdateStrategy, NodeType>;

    /**
     * Inserts a new node with the specified key and value,
     * if the tree does not already contain a node with the same key.
     *
     * @param key Key of the new node.
     * @param value Value of the new node.
     * @return a pair consisting of an pointer and a boolean. The pointer points:
     *  - To the inserted element if the insertion took place.
     *  - To the element that prevented the insertion if tree already contains a node with the same
     * key.
     *  The boolean is true if the new node was successfully inserted, false otherwise.
     */
    std::pair<NodePtr, bool> Insert(
        TKey key, TValue value) requires CallableWithUpdateSignature<TUpdateStrategy, NodeType>;

    /**
     * Searches for the node with the given key.
     *
     * @param key Key to search for.
     * @return NodePtr pointing to the requested node, or nullptr if the node with the requested key
     * was not found.
     */
    NodePtr Find(TKey key);

    /**
     * Searches for the node with the given key among the descendants of this node
     * and removes it from the tree if found.
     *
     * @param key Key for which the node is to be removed.
     * @return Pointer to the removed node.
     */
    NodePtr Remove(TKey key);

    TKey Key() const
    {
        return key_;
    }

    TValue Value() const
    {
        return value_;
    }

    /**
     * Disconnects the direct descendant node in the given direction.
     *
     * @param direction Direction
     * @return Pointer to the disconnected node, or nullptr if the descendant is not found.
     * @note Descendants of the disconnected node remain connected to the disconnected node.
     */
    NodePtr Disconnect(Direction direction);

    const NodePtr& Left() const
    {
        return left_;
    }

    const NodePtr& Right() const
    {
        return right_;
    }

    /**
     * Removes the direct descendant node in the given direction and reconnects any descendants of
     * the removed node.
     *
     * @param direction Indicates whether the left or the right direct descendant is to be removed.
     * @return Pointer to the removed node, or nullptr if the descendant is not found
     */
    NodePtr RemoveNext(Direction direction);

    ConstIterator Begin() const;

    ConstIterator End() const;

private:
    /**
     * Searches for the Node that is parent of the Node with the given key.
     *
     * @param key Key for which the parent node is to be returned.
     * @return Pair consisting of:
     *  - NodePtr pointing to the parent node of the Node with the given key, or nullptr if the key
     * was not found,
     *  - Direction of the descendant with the given key.
     */
    std::pair<NodePtr, Direction> FindParent(TKey key);

    TKey key_;
    TValue value_;

    NodePtr left_;
    NodePtr right_;

    friend TUpdateStrategy;
};

template <typename TUpdateStrategy, std::totally_ordered TKey, typename TValue>
typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr MakeBSTNode(TKey key, TValue value)
{
    return std::make_shared<BSTNode<TKey, TValue, TUpdateStrategy>>(key, value);
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
std::pair<typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr, bool>
BSTNode<TKey, TValue, TUpdateStrategy>::Insert(
    NodePtr new_node) requires CallableWithUpdateSignature<TUpdateStrategy, NodeType>
{
    if (!new_node)
    {
        return {nullptr, false};
    }

    if (new_node->Key() == key_)
    {
        return TUpdateStrategy()(*this, std::move(*new_node));
    }

    if (new_node->Key() < key_)
    {
        if (!left_)
        {
            left_.swap(new_node);
            return {left_, true};
        }
        return left_->Insert(std::move(new_node));
    }

    if (!right_)
    {
        right_.swap(new_node);
        return {right_, true};
    }
    return right_->Insert(std::move(new_node));
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
std::pair<typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr, bool>
BSTNode<TKey, TValue, TUpdateStrategy>::Insert(
    TKey key, TValue value) requires CallableWithUpdateSignature<TUpdateStrategy, NodeType>
{
    return Insert(MakeBSTNode<TUpdateStrategy, TKey, TValue>(key, value));
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr
BSTNode<TKey, TValue, TUpdateStrategy>::Find(TKey key)
{
    if (key == key_)
    {
        return this->shared_from_this();
    }

    if (key > key_)
    {
        return right_ ? right_->Find(key) : nullptr;
    }

    return left_ ? left_->Find(key) : nullptr;
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
std::pair<typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr, Direction>
BSTNode<TKey, TValue, TUpdateStrategy>::FindParent(TKey key)
{
    if (!left_ && !right_)
    {
        return {nullptr, Direction{}};
    }
    if (left_ && key < key_)
    {
        if (left_->Key() == key)
        {
            return {this->shared_from_this(), Direction::kLeft};
        }
        auto found_left = left_->FindParent(key);
        if (found_left.first)
        {
            return found_left;
        }
    }
    if (right_ && key > key_)
    {
        if (right_->Key() == key)
        {
            return {this->shared_from_this(), Direction::kRight};
        }
        return right_->FindParent(key);
    }
    return {nullptr, Direction{}};
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr
BSTNode<TKey, TValue, TUpdateStrategy>::Remove(TKey key)
{
    if (key == key_)
    {
        auto removed_node = MakeBSTNode<TUpdateStrategy>(key_, value_);
        if (left_)
        {
            auto&& right = Disconnect(Direction::kRight);
            key_ = left_->Key();
            value_ = left_->Value();
            right_ = left_->Right();
            left_ = left_->Left();
            Insert(std::move(right));
        }
        else if (right_)
        {
            key_ = right_->Key();
            value_ = right_->Value();
            left_ = right_->Left();
            right_ = right_->Right();
        }
        return removed_node;
    }

    const auto parent_and_direction = FindParent(key);
    if (!parent_and_direction.first)
    {
        return nullptr;
    }

    return parent_and_direction.first->RemoveNext(parent_and_direction.second);
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr
BSTNode<TKey, TValue, TUpdateStrategy>::RemoveNext(Direction direction)
{
    // Removed node with its descendants
    auto removed_node = Disconnect(direction);
    if (!removed_node)
    {
        return nullptr;
    }

    Insert(removed_node->Disconnect(Direction::kLeft));
    Insert(removed_node->Disconnect(Direction::kRight));

    return removed_node;
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
typename BSTNode<TKey, TValue, TUpdateStrategy>::NodePtr
BSTNode<TKey, TValue, TUpdateStrategy>::Disconnect(Direction direction)
{
    NodePtr disconnected_node;
    std::swap(disconnected_node, (direction == Direction::kLeft ? left_ : right_));
    return disconnected_node;
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
typename BSTNode<TKey, TValue, TUpdateStrategy>::ConstIterator
BSTNode<TKey, TValue, TUpdateStrategy>::Begin() const
{
    std::stack<ConstNodePtr> parent_stack;
    auto current = this->shared_from_this();
    ConstIterator::WindLeft(current, parent_stack);
    return BSTNode::ConstIterator(std::move(parent_stack), std::move(current));
}

template <std::totally_ordered TKey, typename TValue, typename TUpdateStrategy>
typename BSTNode<TKey, TValue, TUpdateStrategy>::ConstIterator
BSTNode<TKey, TValue, TUpdateStrategy>::End() const
{
    return BSTNode::ConstIterator(std::stack<ConstNodePtr>{}, nullptr);
}

#endif  // BINARY_SEARCH_TREE_BST_NODE_HPP
