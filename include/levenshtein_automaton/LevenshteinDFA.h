#pragma once

#include "Trie.h"
#include "LevenshteinNFA.h"

#include <list>
#include <map>

namespace la
{
    class LevenshteinDFA
    {
    public:
        LevenshteinDFA();
        ~LevenshteinDFA();
        static LevenshteinDFA* SubsetConstruct(LevenshteinNFA *nfa);
        static std::list<int> EpsilonClosure(LevenshteinNFA *nfa, std::list<int> states);
        int start;
        std::list<int> *finalStates;
        std::map<std::pair<int, char>, int> *transTable;
        std::map<int, int> *defaultTrans;
        std::list<char> uniqueChars;
        void Search(Trie *trie, int start, TrieNode* node, std::list<std::string> &output);
    };
}