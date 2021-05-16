
#include <string>
#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <ctime>

#include "levenshtein_automaton/Trie.h"
#include "levenshtein_automaton/LevenshteinNFA.h"
#include "levenshtein_automaton/LevenshteinDFA.h"
using namespace std;
int START=0;
int main(int argc, char **argv)
{
    ifstream file;
    Trie trie;
    clock_t timer;
    double duration = 0;
    double totalTime = 0;
    int maxDist = 2;
    char line[256];

    LevenshteinAutomata::LevenshteinNFA *nfa;
    LevenshteinAutomata::LevenshteinDFA *dfa;
    trie.rootNode = getNode(' ', "");
    file.open("../resources/wordList.txt");
    cout << "Constructing Trie..."<< endl;
    timer = clock();
    /*Load in all resources*/
    while (file.good())
    {
        file.getline(line,256);
        trie.Insert(line);
    }
    file.close();
    duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
    cout << "Constructing Trie Complete! Time: " << duration << " Seconds" << endl;
    cout << "Levenshteins Distance: " << maxDist << endl;
    file.open("../resources/wordsToTest.txt");
    //Search
    while (file.good())
    {
        file.getline(line, 256);
        cout << "===================================================================" << endl;
        cout << "Constructing Levenshteins Automata for word: " << line << endl;
        timer = clock();

        nfa = LevenshteinAutomata::LevenshteinNFA::ConstructNFA(line, maxDist);
        dfa = LevenshteinAutomata::LevenshteinDFA::SubsetConstruct(nfa);
        list<string> output;
        cout << "Searching..." << endl;
        dfa->Search(&trie, dfa->start, trie.rootNode, output);
        duration = (clock() - timer) / (double)CLOCKS_PER_SEC;
        totalTime += duration;
        cout << "Construction and Search complete! Time: " << duration << " Seconds" << endl;
        /*for(auto it = output.begin();it!=output.end();it++){
            cout<<*it<<endl;
        }*/
        cout << "Number of hits found: " << output.size() << endl;

    }
    cout << "Total time: " << totalTime << " Seconds.."<<endl;
    file.close();
    //Clean Up
    delete nfa;
    delete dfa;
//    char c = getchar();
    return 0;

}