#include "levenshtein_automaton/trie_node.h"

namespace la
{
    trie_node::trie_node(const char &key, std::string &&value)
        : key{key},
        value{std::move(value)},
        is_end_word{false},
        children{nullptr} {}

    trie_node::~trie_node()
    {
        for (auto &&child : children)
            if(child != nullptr)
                delete child;
    }
}