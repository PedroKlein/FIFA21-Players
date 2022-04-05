#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#define ALPHABET_SIZE 26

using namespace std;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int fifaID;
    bool isEndOfWord;
} typedef TrieNode;

class TrieTree
{
private:
    TrieNode *root;
    TrieNode *getNode(void);

public:
    TrieTree(void);
    ~TrieTree();
    void insert(string key, int fifaID);
    int search(string key);
};