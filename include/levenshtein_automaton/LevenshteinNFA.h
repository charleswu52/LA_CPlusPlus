#pragma once

#include <string>
#include <vector>
#include <list>
#include <forward_list>

namespace LevenshteinAutomata
{

    class LevenshteinNFA
    {
    public:
        LevenshteinNFA(int size, int state, std::list<int> finalStates);
        ~LevenshteinNFA();

        enum Constants
        {
            Deletion = '|',
            Dead = '\0',
            Insertion = '~'
        };
        static LevenshteinNFA* ConstructNFA(std::string str, int maxDist);
        void AddTransition(int from, int to, char input);
        std::list<int> Move(std::list<int> states, char inp);
        void Show();

        int initialState;
        std::list<int> finalStates;
        std::forward_list<char> inputs;
        std::vector<char> *transTable;
        //char** transTable;
        int size;
    };
}