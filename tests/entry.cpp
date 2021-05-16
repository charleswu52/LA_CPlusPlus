#include "levenshtein_automaton/Trie.h"
#include "levenshtein_automaton/LevenshteinNFA.h"
#include "levenshtein_automaton/LevenshteinDFA.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <ctime>

static const std::string documents_path{"../resources/wordList.txt"};
static const std::string queries_path{"../resources/wordsToTest.txt"};

std::vector<std::string>
read_all_lines(const std::string &path)
{
    std::vector<std::string> result;
    std::ifstream ifs{path, std::ifstream::in};
    std::string line;
    while (getline(ifs, line))
        result.push_back(std::move(line));
    ifs.close();
    return result;
}

int la::START = 0;
int main(int argc, char *argv[])
{
    std::vector<std::string> documents{read_all_lines(documents_path)};
    std::vector<std::string> queries{read_all_lines(queries_path)};

    la::Trie trie;
    clock_t timer;
    double duration = 0;
    double totalTime = 0;
    int maxDist = 2;

    la::LevenshteinNFA *nfa;
    la::LevenshteinDFA *dfa;
    trie.rootNode = la::getNode(' ', "");
    std::cout << "Constructing Trie..." << std::endl;
    timer = clock();
    /*Load in all resources*/
    for (auto &&document : documents)
        trie.Insert(document);
    duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
    std::cout << "Constructing Trie Complete! Time: " << duration << " Seconds" << std::endl;
    std::cout << "Levenshteins Distance: " << maxDist << std::endl;
    //Search
    for (auto &&query : queries)
    {
        std::cout << "===================================================================" << std::endl;
        std::cout << "Constructing Levenshteins Automata for word: " << query << std::endl;
        timer = clock();

        nfa = la::LevenshteinNFA::ConstructNFA(query, maxDist);
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
    //Clean Up
    delete nfa;
    delete dfa;
    return 0;
}