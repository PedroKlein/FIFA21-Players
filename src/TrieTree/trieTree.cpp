#include "trieTree.h"

TrieNode::TrieNode()
{
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
        this->children[i] = std::shared_ptr<TrieNode>();

    this->isEndOfWord = false;
}

TrieNode::~TrieNode(){};

TrieTree::TrieTree()
{
    this->root = std::shared_ptr<TrieNode>(new TrieNode);
    this->totalWords = 0;
}

TrieTree::~TrieTree() {}

void TrieTree::insert(std::string_view key, uint32_t fifaID)
{
    std::shared_ptr<TrieNode> pCrawl = this->root;

    for (size_t i = 0; i < key.length(); i++)
    {
        int index = this->getIndex(key[i]);
        if (index == -1)
            throw;
        if (!pCrawl->children[index])
            pCrawl->children[index] = std::shared_ptr<TrieNode>(new TrieNode);

        pCrawl = pCrawl->children[index];
    }

    this->totalWords++;
    pCrawl->isEndOfWord = true;
    pCrawl->fifaID = fifaID;
    return;
}

std::vector<uint32_t> TrieTree::search(std::string_view key)
{
    std::shared_ptr<TrieNode> pCrawl = this->root;
    std::vector<uint32_t> res;

    for (size_t i = 0; i < key.length(); i++)
    {
        int index = this->getIndex(key[i]);
        if (index == -1 || !pCrawl->children[index])
            return {};

        pCrawl = pCrawl->children[index];
    }

    getAllIDs(pCrawl.get(), res);

    return res;
}

int TrieTree::getIndex(char c)
{
    switch (c)
    {
    case '\"':
        return ALPHABET_SIZE - 5;
        break;
    case ' ':
        return ALPHABET_SIZE - 4;
    case '.':
        return ALPHABET_SIZE - 3;
    case '-':
        return ALPHABET_SIZE - 2;
    case '\'':
        return ALPHABET_SIZE - 1;

    default:
        int index = c - 'a';

        if (index < 0 || index > 26)
            return -1;

        return index;
    }
}

void TrieTree::getAllIDs(TrieNode *root, std::vector<uint32_t> &ids)
{
    if (!root)
        return;
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        getAllIDs(root->children[i].get(), ids);

        if (root->children[i] && root->children[i]->isEndOfWord)
            ids.push_back(root->children[i]->fifaID);
    }
}