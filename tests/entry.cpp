#include "levenshtein_automaton/Trie.h"
#include "levenshtein_automaton/LevenshteinNFA.h"
#include "levenshtein_automaton/LevenshteinDFA.h"

#include <string>
#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <ctime>


int la::START = 0;
int main(int argc, char **argv)
{
    std::ifstream file;
    la::Trie trie;
    clock_t timer;
    double duration = 0;
    double totalTime = 0;
    int maxDist = 2;
    char line[256];

    la::LevenshteinNFA *nfa;
    la::LevenshteinDFA *dfa;
    trie.rootNode = la::getNode(' ', "");
    file.open("../resources/wordList.txt");
    std::cout << "Constructing Trie..." << std::endl;
    timer = clock();
    /*Load in all resources*/
    while (file.good())
    {
        file.getline(line, 256);
        trie.Insert(line);
    }
    file.close();
    duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
    std::cout << "Constructing Trie Complete! Time: " << duration << " Seconds" << std::endl;
    std::cout << "Levenshteins Distance: " << maxDist << std::endl;
    file.open("../resources/wordsToTest.txt");
    //Search
    while (file.good())
    {
        file.getline(line, 256);
        std::cout << "===================================================================" << std::endl;
        std::cout << "Constructing Levenshteins Automata for word: " << line << std::endl;
        timer = clock();

        nfa = la::LevenshteinNFA::ConstructNFA(line, maxDist);
        dfa = la::LevenshteinDFA::SubsetConstruct(nfa);
        std::list<std::string> output;
        std::cout << "Searching..." << std::endl;
        dfa->Search(&trie, dfa->start, trie.rootNode, output);
        duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
        totalTime += duration;
        std::cout << "Construction and Search complete! Time: " << duration << " Seconds" << std::endl;
        /*for(auto it = output.begin();it!=output.end();it++){
            cout<<*it<<endl;
        }*/
        std::cout << "Number of hits found: " << output.size() << std::endl;
    }
    std::cout << "Total time: " << totalTime << " Seconds.." << std::endl;
    file.close();
    //Clean Up
    delete nfa;
    delete dfa;
    return 0;
}