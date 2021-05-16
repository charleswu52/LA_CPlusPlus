#include "levenshtein_automaton/trie_node.h"

namespace la
{
    trie_node::trie_node(const char &key, std::string &&value)
        : _key{key},
        _value{std::move(value)},
        _is_end_word{false},
        _children{nullptr} {}

    trie_node::~trie_node()
    {
        for (auto &&child : _children)
            if(child != nullptr)
                delete child;
    }
}