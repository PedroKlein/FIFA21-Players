#pragma once

#include <vector>
#include <memory>
#include "hashTableIterator.h"

template <typename T, size_t N>
class HashTable
{
public:
    using Iterator = HashTableIterator<HashTable<T, N>, N>;
    using ValueType = T;
    using HashItem = std::pair<uint32_t, T>;
    using HashPosition = std::vector<HashItem>;

private:
    std::unique_ptr<HashPosition[]> items;
    size_t capacity = 0;
    size_t size = 0;
    size_t colisions = 0;
    size_t maxColisions = 0;

public:
    HashTable()
    {
        this->capacity = N;
        items = std::make_unique<HashPosition[]>(N);
    }

    ~HashTable()
    {
    }

    size_t getCapacity()
    {
        return capacity;
    }

    size_t getSize()
    {
        return size;
    }

    size_t getColisions()
    {
        return colisions;
    }

    size_t getMaxColisions()
    {
        return maxColisions;
    }

    // TODO: improve hash function
    size_t hash(const uint32_t &key)
    {
        uint32_t hash = key * 7;

        return hash % capacity;
    }

    Iterator insert(HashItem item)
    {
        auto index = hash(item.first);
        // if (items[index].size() > 0)
        //     maxColisions = items[index].size() + 1 > maxColisions ? items[index].size() + 1 : maxColisions;

        items[index].push_back(item);
        size++;
        return Iterator(items, index, items[index].end() - 1);
    }

    template <typename... Args>
    Iterator emplace(uint32_t key, Args &&...args)
    {
        // HashItem<T> item(key, std::forward<Args>(args)...);
        auto index = hash(key);
        // if (items[index].size() > 0)
        //     maxColisions = items[index].size() + 1 > maxColisions ? items[index].size() + 1 : maxColisions;

        items[index].emplace_back(key, std::forward<Args>(args)...);
        size++;
        return Iterator(items, index, items[index].end() - 1);
    }

    Iterator find(const uint32_t &key)
    {
        auto index = hash(key);

        for (auto i = items[index].begin(); i != items[index].end(); ++i)
        {
            if (i->first == key)
            {
                return Iterator(items, index, i);
            }
        }

        return end();
    }

    Iterator begin()
    {
        auto it = Iterator(items, 0, items[0].begin());
        if (items[0].begin() == items[0].end())
            it++;
        return it;
    }

    Iterator end()
    {
        return Iterator(items, N, items[N - 1].end());
    }
};
