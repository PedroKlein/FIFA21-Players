#pragma once

#include <vector>
#include <memory>

template <typename K, typename T, size_t N>
class HashTable
{
public:
    using HashItem = std::pair<K, T>;
    using HashPosition = std::vector<HashItem>;

private:
    std::unique_ptr<HashPosition[]> items;
    size_t capacity = 0;
    size_t size = 0;

public:
    HashTable()
    {
        capacity = N;
        items = std::unique_ptr<HashPosition[]>(new HashPosition[capacity]);
    }

    ~HashTable() {}

    size_t getCapacity()
    {
        return capacity;
    }

    size_t getSize()
    {
        return size;
    }

    // TODO: improve hash function
    size_t hash(uint32_t key) const
    {
        size_t hash = key * 7;

        return hash % capacity;
    }

    size_t hash(std::string_view key) const
    {
        size_t hash = 0;

        for (size_t i = 0; i < key.length(); i++)
            hash = (hash * 7) + key[i];

        return hash % capacity;
    }

    typename HashPosition::iterator insert(const HashItem &item)
    {
        size_t index = hash(item.first);

        items[index].push_back(item);
        size++;
        return items[index].end() - 1;
    }

    template <typename... Args>
    typename HashPosition::iterator emplace(K key, Args &&...args)
    {
        size_t index = hash(key);

        items[index].emplace_back(key, std::forward<Args>(args)...);
        size++;
        return items[index].end() - 1;
    }

    std::pair<typename HashPosition::iterator, bool> find(K key)
    {
        size_t index = hash(key);

        for (auto i = items[index].begin(); i != items[index].end(); ++i)
        {
            if (i->first == key)
            {
                return {i, true};
            }
        }

        return {end(), false};
    }

    typename HashPosition::iterator end()
    {
        return items[capacity - 1].end();
    }
};
