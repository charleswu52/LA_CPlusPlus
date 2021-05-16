cmake_minimum_required(VERSION 3.17)
project(LA_C__)

set(CMAKE_CXX_STANDARD 11)

add_executable(LA_C__ tests/entry.cpp LevenshteinDFA.cpp LevenshteinDFA.h LevenshteinNFA.cpp LevenshteinNFA.h Trie.cpp Trie.h)