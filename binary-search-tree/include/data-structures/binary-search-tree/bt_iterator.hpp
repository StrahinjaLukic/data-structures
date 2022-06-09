//
// Created by strahinja on 5/26/22.
//

#ifndef BINARY_TREE_BT_ITERATOR_HPP
#define BINARY_TREE_BT_ITERATOR_HPP

#include <memory>
#include <utility>
#include <stack>

template<typename TKey, typename TValue>
class BSTNode;

template<typename... TArgs>
class BinaryTreeConstIterator {
public:
    using ThisType = BinaryTreeConstIterator<TArgs...>;
    using NodeType = BSTNode<TArgs...>;
    using ConstNodePtr = std::shared_ptr<const NodeType>;

    static void WindLeft(ConstNodePtr &node_ptr, std::stack<ConstNodePtr> &parent_stack) {
        while (auto &left = node_ptr->Left()) {
            parent_stack.push(node_ptr);
            node_ptr = left;
        }
    }

    BinaryTreeConstIterator &operator++() {
        if (!current_item_) {
            auto empty_stack = std::stack<ConstNodePtr>{};
            parent_stack_.swap(empty_stack);
            return *this;
        }
        if (current_item_->Right()) {
            current_item_ = current_item_->Right();
            WindLeft(current_item_, parent_stack_);
            return *this;
        }
        if (parent_stack_.empty()) {
            current_item_.reset();
            return *this;
        }
        current_item_ = parent_stack_.top();
        parent_stack_.pop();
        return *this;
    }

    const NodeType &operator*() {
        return *current_item_;
    }

    bool operator==(const ThisType &other) const {
        return current_item_ == other.current_item_ &&
               parent_stack_.empty() == other.parent_stack_.empty() &&
               (parent_stack_.empty() ||
                parent_stack_.top() == other.parent_stack_.top());
    }

    bool operator!=(const ThisType &other) const {
        return !(*this == other);
    }

private:
    BinaryTreeConstIterator(std::stack<ConstNodePtr> parent_stack, ConstNodePtr current_item) :
            parent_stack_(std::move(parent_stack)),
            current_item_(std::move(current_item)) {}

    friend NodeType;

    std::stack<ConstNodePtr> parent_stack_;
    ConstNodePtr current_item_;
};

#endif // BINARY_TREE_BT_ITERATOR_HPP
