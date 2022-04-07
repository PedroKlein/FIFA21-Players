#pragma once

#include <vector>
#include <memory>

template <typename T>
using HashItem = std::pair<uint32_t, T>;

template <typename T>
using HashPosition = std::vector<HashItem<T>>;

template <typename T>
class HashTable
{
private:
    std::unique_ptr<HashPosition<T>[]> items;
    size_t capacity = 0;
    size_t size = 0;
    size_t colisions = 0;
    size_t maxColisions = 0;

public:
    HashTable(size_t capacity)
    {
        this->capacity = capacity;
        items = std::unique_ptr<HashPosition<T>[]>(new HashPosition<T>[capacity]);
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
    uint32_t hash(uint32_t key)
    {
        uint32_t hash = key * 7;

        return hash % capacity;
    }

    void insert(HashItem<T> item)
    {
        unsigned long index = hash(item.first);
        if (items[index].size() > 0)
            maxColisions = items[index].size() + 1 > maxColisions ? items[index].size() + 1 : maxColisions;

        items[index].push_back(item);
        size++;
    }

    template <typename... Args>
    void emplace(Args &&...args)
    {
        HashItem<T> item(std::forward<Args>(args)...);
        unsigned long index = hash(item.first);
        if (items[index].size() > 0)
            maxColisions = items[index].size() + 1 > maxColisions ? items[index].size() + 1 : maxColisions;

        items[index].push_back(item);
        size++;
    }

    typename HashPosition<T>::iterator find(uint32_t key)
    {
        uint32_t index = hash(key);

        for (auto i = items[index].begin(); i != items[index].end(); ++i)
        {
            if (i->first == key)
            {
                return i;
            }
        }

        return end();
    }

    typename HashPosition<T>::iterator end()
    {
        // TODO: fix gambiarra
        return items[0].end();
    }
};
