//
// Created by strahinja on 6/19/22.
//

#include <data-structures/concepts/bt_concepts.hpp>

namespace
{
struct NodeWithAPtr
{
    using NodePtr = int;
};

template <typename TReturnType, typename... TArgs>
struct TTestCallable
{
    TReturnType operator()(TArgs...)
    {
        return TReturnType{};
    }
};

using CorrectReturnType = std::pair<NodeWithAPtr::NodePtr, bool>;

using TCallableWithUpdateSignature =
    TTestCallable<CorrectReturnType, NodeWithAPtr&, NodeWithAPtr&&>;
using TWrongArgsLvalueSource = TTestCallable<CorrectReturnType, NodeWithAPtr&, NodeWithAPtr&>;
using TWrongArgsWrongTarget = TTestCallable<CorrectReturnType, NodeWithAPtr*, NodeWithAPtr&&>;
using TWrongArgsOneArg = TTestCallable<CorrectReturnType, NodeWithAPtr&>;
using TWrongReturnType = TTestCallable<int, NodeWithAPtr&, NodeWithAPtr&&>;
}  // namespace

static_assert(CallableWithUpdateSignature<TCallableWithUpdateSignature, NodeWithAPtr>);
static_assert(not CallableWithUpdateSignature<TWrongArgsLvalueSource, NodeWithAPtr>);
static_assert(not CallableWithUpdateSignature<TWrongArgsWrongTarget, NodeWithAPtr>);
static_assert(not CallableWithUpdateSignature<TWrongArgsOneArg, NodeWithAPtr>);
static_assert(not CallableWithUpdateSignature<TWrongReturnType, NodeWithAPtr>);
