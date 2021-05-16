#pragma once

#include <string>

const int ALPHABET_SIZE = 26;

typedef struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndWord;
    char key;
    std::string  value;
}TrieNode;

TrieNode *getNode(char key, std::string value);

extern int START;

class Trie
{
public:
    Trie();
    TrieNode* rootNode;
    void Insert(std::string key);
    bool Search(std::string key);
};