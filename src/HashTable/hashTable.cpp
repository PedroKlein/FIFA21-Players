#include "hashTable.h"

HashTable::HashTable(unsigned long capacity)
{
    this->capacity = capacity;

    items = (HashPosition **)calloc(capacity, sizeof(HashPosition *));

    for (size_t i = 0; i < capacity; i++)
        items[i] = NULL;
}

HashTable::~HashTable()
{
    for (size_t i = 0; i < capacity; i++)
        delete items[i];

    free(items);
}

unsigned long HashTable::getCapacity()
{
    return capacity;
}
unsigned long HashTable::getSize()
{
    return size;
}

unsigned long HashTable::hash(std::string str)
{
    int seed = 7;
    unsigned long hash = 0;

    for (size_t i = 0; i < str.length(); i++)
        hash = (hash * seed) + str[i];

    return hash % capacity;
}

void HashTable::insert(HashItem item)
{
    unsigned long index = hash(item.key);

    if (items[index] == NULL)
        items[index] = new HashPosition();

    items[index]->push_back(item);
    size++;
}

int HashTable::search(std::string key)
{
    unsigned long index = hash(key);

    if (items[index] == NULL)
        return -1;

    int accesses = 1;

    for (auto &&i : *items[index])
    {
        if (i.key == key)
            return accesses;
        accesses++;
    }

    return -1;
}
