#pragma once

#include <vector>
template <typename HashTableType>
class HashTableIterator
{
public:
    using Iterator = HashTableIterator<HashTableType>;

    using IteratorCategory = std::forward_iterator_tag;
    using ValueType = typename HashTableType::ValueType;
    using DataStructType = typename std::vector<std::pair<uint32_t, ValueType>>;
    using VectorIterator = typename std::vector<std::pair<uint32_t, ValueType>>::iterator;

    using DataStructPointer = DataStructType *;
    using DataStructReference = DataStructType &;

    using PointerType = ValueType *;
    using ReferenceType = ValueType &;

    using DifferenceType = std::ptrdiff_t;

public:
    HashTableIterator(DataStructPointer ptr, VectorIterator vecIt)
        : mPtr(ptr),
          vectorIterator(vecIt) {}
    ~HashTableIterator() {}

    Iterator &operator++()
    {
        if (vectorIterator == mPtr->end())
            mPtr++;

        vectorIterator++;

        return *this;
    }

    Iterator operator++(int)
    {
        Iterator iterator = *this;
        ++(*this);
        return iterator;
    }

    Iterator &operator--()
    {
        mPtr--;
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator iterator = *this;
        --(*this);
        return iterator;
    }

    // PointerType operator->()
    // {
    //     vectorIterator->
    //     return dynamic_cast<PointerType>(*(vectorIterator->second));
    // }

    ReferenceType operator*()
    {
        return vectorIterator->second;
    }

    bool operator==(const HashTableIterator &other) const
    {
        return mPtr == other.mPtr;
    }

    bool operator!=(const HashTableIterator &other) const
    {
        return !(*this == other);
    }

protected:
    DataStructPointer mPtr;
    VectorIterator vectorIterator;
};
