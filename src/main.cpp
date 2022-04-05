#include <iostream>
#include <hashTable.h>
#include <trieTree.h>
#include <parser.hpp>

int main(int argc, char const *argv[])
{
  // HashTable hashTable(10000);

  // std::ifstream f("../data/minirating.csv");
  // aria::csv::CsvParser parser(f);

  // for (auto &row : parser)
  // {
  //   hashTable.insert({row[0], row[1]});
  // }

  // std::cout << hashTable.getSize();

  TrieTree trie;

  string keys[] = {"the", "a", "there",
                   "answer", "any", "by",
                   "bye", "their"};
  int n = sizeof(keys) / sizeof(keys[0]);

  // Construct trie
  for (int i = 0; i < n; i++)
    trie.insert(keys[i], i);

  // Search for different keys
  trie.search("the") >= 0 ? cout << "Searching for THEN: found\n" : cout << "Searching for THEN: not found\n";
  trie.search("these") >= 0 ? cout << "Searching for THESE: found\n" : cout << "Searching for THESE: not found\n";
  trie.search("an") >= 0 ? cout << "Searching for AN: found\n" : cout << "Searching for AN: not found\n";
  trie.search("a") >= 0 ? cout << "Searching for A: found\n" : cout << "Searching for A: not found\n";
  trie.search("any") >= 0 ? cout << "Searching for ANY: found\n" : cout << "Searching for ANY: not found\n";
  trie.search("anyb") >= 0 ? cout << "Searching for ANYB: found\n" : cout << "Searching for ANYB: not found\n";

  return 0;
}
