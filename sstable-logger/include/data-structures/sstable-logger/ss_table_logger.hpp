//
// Created by strahinja on 7/23/22.
//

#ifndef DATA_STRUCTURES_SS_TABLE_LOGGER_HPP
#define DATA_STRUCTURES_SS_TABLE_LOGGER_HPP

#include <data-structures/binary-search-tree/bst_node.hpp>
#include <data-structures/binary-search-tree/bt_update_strategies.hpp>

#include <cstdint>
#include <optional>
#include <tuple>

/**
 * Logger class that writes log entries in an arbitrary order and reads them sorted by key.
 *
 * @tparam Args parameter type pack that determines the type of an entry.
 */
template <typename... Args>
class SSTableLogger
{
public:
    using KeyType = std::int64_t;

    /**
     * Logs an entry consisting of values contained in the args pack under key.
     * @param key Key under which to log the entry.
     * @param args Arguments for the entry.
     */
    void Log(KeyType key, Args... args);

    /**
     * Retrieves the latest entry logged under key, if any.
     * @param key Key under which to search for the entry
     * @return A tuple of values corresponding to the requested entry, or nullopt if not found.
     */
    std::optional<std::tuple<Args...>> Retrieve(KeyType key);

private:
    using MemtableNode =
        BSTNode<KeyType, std::tuple<Args...>, AcceptUpdates<KeyType, std::tuple<Args...>>>;
    typename MemtableNode::NodePtr memtable_;
};

template <typename... Args>
void SSTableLogger<Args...>::Log(SSTableLogger::KeyType key, Args... args)
{
    if (!memtable_)
    {
        memtable_ = MakeBSTNode<AcceptUpdates<KeyType, std::tuple<Args...>>>(
            key, std::make_tuple(std::move(args)...));
    }
}

template <typename... Args>
std::optional<std::tuple<Args...>> SSTableLogger<Args...>::Retrieve(SSTableLogger::KeyType key)
{
    if (!memtable_)
    {
        return {};
    }

    auto node_ptr = memtable_->Find(key);
    if (!node_ptr)
    {
        return {};
    }

    return node_ptr->Value();
}

#endif  // DATA_STRUCTURES_SS_TABLE_LOGGER_HPP
