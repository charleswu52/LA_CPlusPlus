#include "levenshtein_automaton/trie_tree.h"
#include "levenshtein_automaton/LevenshteinNFA.h"
#include "levenshtein_automaton/LevenshteinDFA.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <chrono>

static const std::string documents_path{"../resources/wordList.txt"};
static const std::string queries_path{"../resources/wordsToTest.txt"};

static constexpr int maxDist = 2;

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
    la::trie_tree tree;
    tree.rootNode = new la::TrieNode{' ', ""};
    auto documents{read_all_lines(documents_path)};
    std::cout << "Constructing Trie...\n";
    auto timer{std::chrono::high_resolution_clock::now()};
    /*Load in all resources*/
    for (auto &&document : documents)
        tree.insert(std::move(document));
    auto duration{std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timer).count()};
    std::cout << "Constructing Trie Complete! Time: " << duration << " Microseconds\n";

    //Search
    auto queries{read_all_lines(queries_path)};
    decltype(duration) totalTime{0};
    std::cout << "Levenshteins Distance: " << maxDist << '\n';
    for (auto &&query : queries)
    {
        std::cout << "===================================================================\n";
        std::cout << "Constructing Levenshteins Automata for word: " << query << '\n';
        timer = std::chrono::high_resolution_clock::now();

        std::unique_ptr<la::LevenshteinNFA> nfa{la::LevenshteinNFA::ConstructNFA(query, maxDist)};
        std::unique_ptr<la::LevenshteinDFA> dfa{la::LevenshteinDFA::SubsetConstruct(nfa.get())};
        std::list<std::string> output;
        std::cout << "Searching...\n";
        dfa->Search(&tree, dfa->start, tree.rootNode, output);
        duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timer).count();
        totalTime += duration;
        std::cout << "Construction and Search complete! Time: " << duration << " Microseconds\n";
        /*
        for(const auto &word : output)
            std::cout<< word << '\n';
        */
        std::cout << "Number of hits found: " << output.size() << '\n';
    }
    std::cout << "Total time: " << totalTime << " Microseconds..\n";
    return 0;
}