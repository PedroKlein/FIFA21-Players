#include <iostream>
#include <hashTable.h>

int main(int argc, char const *argv[])
{
    HashTable hashTable(5);
    hashTable.insert({"hello", "utzig"});
    hashTable.insert({"key", "value"});
    std::cout << hashTable.getSize();
    return 0;
}
