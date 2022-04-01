#pragma once

#include <vector>
#include <string>


struct HashItem
{
    std::string key;
    std::string value;

    bool operator==(const HashItem &item) const
    {
        return (key == item.key && value == item.value);
    }
};

typedef std::vector<HashItem> HashPosition;

class HashTable
{
private:
    HashPosition **items;
    unsigned long capacity = 0;
    unsigned long size = 0;

public:
    HashTable(unsigned long capacity);
    ~HashTable();

    unsigned long getCapacity();
    unsigned long getSize();
    unsigned long hash(std::string str);
    void insert(HashItem item);
    int search(std::string key);
};
