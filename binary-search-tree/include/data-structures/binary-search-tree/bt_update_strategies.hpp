//
// Created by strahinja on 6/9/22.
//

#ifndef BINARY_SEARCH_TREE_BT_UPDATE_STRATEGIES_HPP
#define BINARY_SEARCH_TREE_BT_UPDATE_STRATEGIES_HPP

#include <utility>

template<typename TKey, typename TValue, typename TUpdateStrategy>
class BSTNode;

template<typename... TArgs>
class RejectUpdates {
    using Node = BSTNode<TArgs..., RejectUpdates<TArgs...>>;
    using NodePtr = typename Node::NodePtr;
public:
    std::pair<NodePtr, bool> operator()(Node& this_node, Node&& /* new_node */) {
        return {this_node.shared_from_this(), false};
    }
};

template<typename... TArgs>
class AcceptUpdates {
    using Node = BSTNode<TArgs..., AcceptUpdates<TArgs...>>;
    using NodePtr = typename Node::NodePtr;
public:
    std::pair<NodePtr, bool> operator()(Node& this_node, Node&& new_node) {
        this_node.value_ = std::move(new_node.value_);
        return {this_node.shared_from_this(), true};
    }
};

#endif //BINARY_SEARCH_TREE_BT_UPDATE_STRATEGIES_HPP
