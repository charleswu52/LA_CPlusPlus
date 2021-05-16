#pragma once

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <iostream>

namespace la
{
    class LevenshteinNFA
    {
    public:
        LevenshteinNFA(std::size_t size, int state, std::list<int> &&finalStates);

        enum class Constants:char
        {
            Deletion = '|',
            Dead = '\0',
            Insertion = '~'
        };
        static LevenshteinNFA ConstructNFA(const std::string &str, int maxDist);
        void AddTransition(int from, int to, char input);
        std::list<int> Move(const std::list<int> &states, char inp);
        void Show();

        int initialState;
        std::list<int> finalStates;
        std::forward_list<char> inputs;
        std::vector<char> transTable;
        std::size_t size;
    };
}