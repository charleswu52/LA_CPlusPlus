#pragma once

#include "levenshtein_automaton/trie_node.h"

#include <string>
#include <array>

namespace la
{
    extern int START;

    class trie_tree
    {
    public:
        trie_tree();
        trie_node *rootNode;
        void insert(std::string &&key);
        bool Search(std::string key);
    };
}