#pragma once

#include <string>
#include <array>

namespace la
{
    static constexpr int ALPHABET_SIZE{26};

    class TrieNode
    {
    public:
        TrieNode(const char &key, std::string &&value);
        std::array<TrieNode *, ALPHABET_SIZE> children;
        bool is_end_word;
        char key;
        std::string value;
    };

    extern int START;

    class trie_tree
    {
    public:
        trie_tree();
        TrieNode *rootNode;
        void insert(std::string &&key);
        bool Search(std::string key);
    };
}