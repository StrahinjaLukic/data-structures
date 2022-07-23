//
// Created by strahinja on 6/18/22.
//

#ifndef BINARY_SEARCH_TREE_BT_CONCEPTS_HPP
#define BINARY_SEARCH_TREE_BT_CONCEPTS_HPP

#include <concepts>
#include <string>

template <typename TUpdateStrategy, typename TNode>
concept CallableWithUpdateSignature = requires
{
    typename TNode::NodePtr;
    requires std::is_invocable_r_v<std::pair<typename TNode::NodePtr, bool>,
                                   TUpdateStrategy,
                                   TNode&,
                                   TNode&&>;
};

#endif  // BINARY_SEARCH_TREE_BT_CONCEPTS_HPP
