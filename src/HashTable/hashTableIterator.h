#pragma once

#include <vector>
#include <memory>

template <typename HashTableType, size_t N>
class HashTableIterator
{
public:
    using Iterator = HashTableIterator<HashTableType, N>;

    using IteratorCategory = std::forward_iterator_tag;
    using ValueType = typename HashTableType::HashItem;

    using DataStructType = typename HashTableType::HashPosition;
    using VectorIterator = typename DataStructType::iterator;

    using PointerType = ValueType *;
    using ReferenceType = ValueType &;

    using DifferenceType = std::ptrdiff_t;

public:
    HashTableIterator(std::unique_ptr<DataStructType[]> &ptr, size_t i, VectorIterator vecIt)
        : mPtr(ptr),
          index(i),
          vectorIterator(vecIt) {}
    ~HashTableIterator() {}

    Iterator &operator++()
    {
        if (index == N)
            return *this;

        if (vectorIterator != mPtr[index].end())
            vectorIterator++;

        while (vectorIterator == mPtr[index].end() && index != N)
            vectorIterator = mPtr[++index].begin();

        return *this;
    }

    Iterator operator++(int)
    {
        Iterator iterator = *this;
        ++(*this);
        return iterator;
    }

    PointerType operator->()
    {
        return &*vectorIterator;
    }

    ReferenceType operator*()
    {
        return (*vectorIterator);
    }

    bool operator==(const HashTableIterator &other) const
    {
        return vectorIterator == other.vectorIterator;
    }

    bool operator!=(const HashTableIterator &other) const
    {
        return !(*this == other);
    }

protected:
    std::unique_ptr<DataStructType[]> &mPtr;
    size_t index;
    VectorIterator vectorIterator;
};
