#include "levenshtein_automaton/trie_tree.h"

namespace la
{
    trie_tree::trie_tree()
        : _root_node{new trie_node{' ', ""}} {}

    trie_tree::~trie_tree()
    {
        delete _root_node;
    }

    void trie_tree::insert(std::string &&key)
    {
        auto cur_node{_root_node};
        for (decltype(key.size()) i{0}; i < key.size(); ++i)
        {
            const auto ci{key[i] - 'a'};
            if (cur_node->_children[ci] == nullptr)
                cur_node->_children[ci] = new trie_node{key[i], key.substr(0, i + 1)};
            cur_node = cur_node->_children[ci];
        }
        cur_node->_is_end_word = true;
    }

    bool trie_tree::search(const std::string &key)
    {
        auto cur_node{_root_node};
        for (decltype(key.size()) i{0}; i < key.size(); ++i)
        {
            const auto ci{key[i] - 'a'};
            if (cur_node->_children[ci] == nullptr)
                return false;
            cur_node = cur_node->_children[ci];
        }
        return (cur_node != nullptr && cur_node->_is_end_word);
    }
}