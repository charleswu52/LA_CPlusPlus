#include <stack>
#include <algorithm>
#include <set>
#include "levenshtein_automaton/LevenshteinDFA.h"
#include "levenshtein_automaton/trie_tree.h"

namespace la
{
    LevenshteinDFA::LevenshteinDFA()
    {
        finalStates = new std::list<int>();
        defaultTrans = new std::map<int, int>();
        transTable = new std::map<std::pair<int, char>, int>();
        start = START;
    }


    LevenshteinDFA::~LevenshteinDFA()
    {
        free(defaultTrans);
        free(finalStates);
        free(transTable);
    }
    LevenshteinDFA * LevenshteinDFA::SubsetConstruct(LevenshteinNFA * nfa)
    {
        int num = 0;
        LevenshteinDFA* dfa = new LevenshteinDFA();

        std::list<std::list<int>> markedStates;
        std::list<std::list<int>> unmarkedStates;

        std::map<std::list<int>, int> dfaStateNum;

        std::list<int> nfaInitial;
        nfaInitial.emplace_back(nfa->initialState);

        std::list<int> first = EpsilonClosure(nfa, nfaInitial);
        unmarkedStates.emplace_back(first);

        //the initial dfa state
        int dfaInitial = num++;
        dfaStateNum[first] = dfaInitial;

        while (unmarkedStates.size() != 0)
        {
            bool tag=false;
            std::list<int> aState = unmarkedStates.front();
            unmarkedStates.pop_front();

            markedStates.emplace_back(aState);

            //Kinda killer, should redo
            for (std::list<int>::iterator it = aState.begin(); it != aState.end();++it)
            {
                for (std::list<int>::iterator it2 = nfa->finalStates.begin(); it2 != nfa->finalStates.end();++it2)
                {
                    if (*it == *it2)
                    {
                        dfa->finalStates->emplace_back(dfaStateNum[aState]);
                    }
                }
            }
            std::vector<std::pair<std::pair<int,char>,int>> vec_tmp;
//            for each (char c in nfa->inputs)
            for  (char c : nfa->inputs)
            {
                std::list<int> next = EpsilonClosure(nfa, nfa->Move(aState, c));
                if (next.empty()) continue;
                if (std::find(unmarkedStates.begin(), unmarkedStates.end(), next) == unmarkedStates.end() &&
                    std::find(markedStates.begin(), markedStates.end(), next) == markedStates.end())
                {
                    unmarkedStates.emplace_back(next);
                    dfaStateNum.emplace(next, num++);
                }
                if (c != (char)LevenshteinNFA::Constants::Insertion && c != (char)LevenshteinNFA::Constants::Deletion)
                {
                    dfa->uniqueChars.emplace_back(c);
                    std::pair<int, char> transition = std::make_pair(dfaStateNum[aState],c);
                    vec_tmp.push_back(std::pair<std::pair<int,char>,int>(transition,dfaStateNum[next]));
                   // dfa->transTable->insert(std::pair<std::pair<int,char>,int>(transition,dfaStateNum[next]));
                }
                else
                {
                    auto it = dfa->defaultTrans->find(dfaStateNum[aState]);
                    //TODO 数字 ascli值太大
                    if (it == dfa->defaultTrans->end())
                    {
                        dfa->defaultTrans->emplace(dfaStateNum[aState], dfaStateNum[next]);
                        tag = true;
                        for(int i=0;i<vec_tmp.size();i++){
                            if(!(vec_tmp[i].first.first == dfaStateNum[aState]&& vec_tmp[i].second == dfaStateNum[next])){
                                dfa->transTable->insert(std::pair<std::pair<int,char>,int>(vec_tmp[i].first,vec_tmp[i].second));
                            }

                        }
                    }
                }
            }
            if(!tag){
                std::map<int,int> map_tmp;
                for(int i=0;i<vec_tmp.size();i++){
                        map_tmp[vec_tmp[i].second]++;
                }
                for(int i=0;i<vec_tmp.size();i++){
                    //printf("%d %d %d\n",vec_tmp[i].second,map_tmp[vec_tmp[i].second],vec_tmp.size());
                    if(map_tmp[vec_tmp[i].second]==1){
                        dfa->transTable->insert(std::pair<std::pair<int,char>,int>(vec_tmp[i].first,vec_tmp[i].second));
                    }
                    else{
                        dfa->defaultTrans->emplace(vec_tmp[i].first.first,vec_tmp[i].second);
                    }
                }
            }
        }
        dfa->finalStates->sort();
        dfa->finalStates->unique();
        dfa->uniqueChars.sort();
        dfa->uniqueChars.unique();
        return dfa;
    }
    std::list<int> LevenshteinDFA::EpsilonClosure(LevenshteinNFA * nfa, std::list<int> states)
    {
        if (states.empty()) return states;

        std::stack<int> uncheckedStack;

        //Push all states onto stack
        for (std::list<int>::iterator it = states.begin(); it != states.end();++it)
        {
            uncheckedStack.push(*it);
        }

        std::list<int> epsilonClosure = states;

        while (!uncheckedStack.empty())
        {
            int t = uncheckedStack.top();
            uncheckedStack.pop();
            int startIndex = 0;

            for (int i = 0; i < nfa->size;i++)
            {
                char input = nfa->transTable.at((t* nfa->size) + i);
                if (input == (char)la::LevenshteinNFA::Constants::Deletion)
                {
                    if (std::find(epsilonClosure.begin(), epsilonClosure.end(), startIndex) == epsilonClosure.end())
                    {
                        epsilonClosure.emplace_back(startIndex);
                        uncheckedStack.push(startIndex);
                    }
                }
                startIndex++;
            }
        }
        return epsilonClosure;
    }
    void LevenshteinDFA::Search(trie_tree * trie, int start, trie_node * node, std::list<std::string> &output)
    {
        /**/
        if (std::find(finalStates->begin(), finalStates->end(), start) != finalStates->end() &&node->_is_end_word )
        {
            output.emplace_back(node->_value);
        }
        std::list<char> inputs;
        for (std::list<char>::iterator it = uniqueChars.begin(); it != uniqueChars.end();++it)
        {
            std::pair<int, char> pair = std::make_pair(start, *it);
            auto it2 = transTable->find(pair);
            if (it2 != transTable->end())
            {
                inputs.emplace_back(*it);
                for (int i = 0; i < trie_node::ALPHABET_SIZE; ++i)
                {
                    if (node->_children[i] == NULL)
                        continue;
                    if (node->_children[i]->_key == *it)
                    {
                        Search(trie, transTable->at(pair), node->_children[i], output);
                    }
                }
            }
        }
        auto it = defaultTrans->find(start);
        if (it != defaultTrans->end())
        {
            for (int i = 0; i < trie_node::ALPHABET_SIZE; ++i)
            {
                bool found = false;;
                if (node->_children[i] == NULL) continue;
                for (std::list<char>::iterator it = inputs.begin(); it != inputs.end();++it)
                {
                    if (*it == node->_children[i]->_key)
                    {
                        found = true;
                    }
                }
                if (!found)
                {
                    Search(trie, defaultTrans->at(start), node->_children[i], output);
                }
            }
        }

    }
}