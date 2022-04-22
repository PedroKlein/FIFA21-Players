#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define ALPHABET_SIZE 30 // four more because of '.', ' ', '-' and '''

struct TrieNode
{
    std::shared_ptr<TrieNode> children[ALPHABET_SIZE];
    uint32_t fifaID;
    bool isEndOfWord;

    TrieNode();
    ~TrieNode();
};

class TrieTree
{
private:
    std::shared_ptr<TrieNode> root;
    size_t totalWords;

    void getAllIDs(TrieNode *root, std::vector<uint32_t> &ids);

    size_t getIndex(char c);

public:
    TrieTree();
    ~TrieTree();
    void insert(std::string_view key, uint32_t fifaID);
    std::vector<uint32_t> search(std::string_view key);
};