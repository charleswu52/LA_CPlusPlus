#pragma once

#include <string>
#include <array>

namespace la
{
    static constexpr int ALPHABET_SIZE{26};

    class TrieNode
    {
    private:
        TrieNode(const TrieNode &) = delete;
        TrieNode(TrieNode &&) = delete;
        TrieNode &operator=(const TrieNode &) = delete;
        TrieNode &operator=(TrieNode &&) = delete;
    public:
        TrieNode(const char &key, std::string &&value);
        ~TrieNode();
        std::array<TrieNode *, ALPHABET_SIZE> children;
        bool is_end_word;
        char key;
        std::string value;
    };
}