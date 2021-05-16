#include "levenshtein_automaton/trie_tree.h"

namespace la
{
    trie_tree::trie_tree()
    {
    }

    void trie_tree::insert(std::string &&key)
    {
        trie_node *pCrawl = rootNode;
        std::string k = "";

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            k += key[i];
            if (!pCrawl->children[index])
                pCrawl->children[index] = new trie_node{key[i], key.substr(0, i + 1)};

            pCrawl = pCrawl->children[index];
        }

        // mark last node as leaf
        pCrawl->is_end_word = true;
    }

    bool trie_tree::Search(std::string key)
    {
        struct trie_node *pCrawl = rootNode;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                return false;

            pCrawl = pCrawl->children[index];
        }

        return (pCrawl != NULL && pCrawl->is_end_word);
    }
}