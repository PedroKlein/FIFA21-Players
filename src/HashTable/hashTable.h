#pragma once

#include <vector>
#include <memory>
#include "hashTableIterator.h"

template <typename T>
using HashItem = std::pair<uint32_t, T>;

template <typename T>
using HashPosition = std::vector<HashItem<T>>;

template <typename T, size_t N>
class HashTable
{
private:
    std::unique_ptr<HashPosition<T>[]> items;
    size_t capacity = 0;
    size_t size = 0;
    size_t colisions = 0;
    size_t maxColisions = 0;

public:
    using Iterator = HashTableIterator<HashTable<T, N>>;
    using ValueType = T;

public:
    HashTable()
    {
        this->capacity = N;
        items = std::make_unique<HashPosition<T>[]>(N);
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
    uint32_t hash(const uint32_t &key)
    {
        uint32_t hash = key * 7;

        return hash % capacity;
    }

    Iterator insert(HashItem<T> item)
    {
        unsigned long index = hash(item.first);
        if (items[index].size() > 0)
            maxColisions = items[index].size() + 1 > maxColisions ? items[index].size() + 1 : maxColisions;

        items[index].push_back(item);
        size++;
        return &(items[index].back().second);
    }

    template <typename... Args>
    Iterator emplace(uint32_t key, Args &&...args)
    {
        // HashItem<T> item(key, std::forward<Args>(args)...);
        unsigned long index = hash(key);
        if (items[index].size() > 0)
            maxColisions = items[index].size() + 1 > maxColisions ? items[index].size() + 1 : maxColisions;

        items[index].emplace_back(key, std::forward<Args>(args)...);
        size++;
        return &(items[index].back().second);
    }

    std::pair<Iterator, bool> find(const uint32_t &key)
    {
        uint32_t index = hash(key);

        for (auto i = items[index].begin(); i != items[index].end(); ++i)
        {
            if (i->first == key)
            {
                return {&(i->second), true};
            }
        }

        return {nullptr, false};
    }

    Iterator begin()
    {
        return Iterator(&(items[0][0]->second));
    }

    Iterator end()
    {
        return nullptr;
    }
};
