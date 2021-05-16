#include "levenshtein_automaton/trie_node.h"

namespace la
{
    TrieNode::TrieNode(const char &key, std::string &&value)
        : key{key},
        value{std::move(value)},
        is_end_word{false},
        children{nullptr} {}

    TrieNode::~TrieNode()
    {
        for (auto &&child : children)
            if(child != nullptr)
                delete child;
    }
}