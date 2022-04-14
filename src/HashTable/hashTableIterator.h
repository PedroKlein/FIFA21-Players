

template <typename HashTableType>
class HashTableIterator
{
public:
    using Iterator = HashTableIterator<HashTableType>;
    using IteratorCategory = std::forward_iterator_tag;
    using ValueType = typename HashTableType::ValueType;
    using PointerType = ValueType *;
    using ReferenceType = ValueType &;
    using DifferenceType = std::ptrdiff_t;

public:
    HashTableIterator(PointerType ptr)
        : mPtr(ptr) {}
    ~HashTableIterator() {}

    Iterator &operator++()
    {
        mPtr++;
        return *this;
    }

    Iterator operator++(int)
    {
        HashTableIterator iterator = *this;
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
        HashTableIterator iterator = *this;
        --(*this);
        return iterator;
    }

    PointerType operator->()
    {
        return mPtr;
    }

    ReferenceType operator*()
    {
        return *mPtr;
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
    PointerType mPtr;
};
