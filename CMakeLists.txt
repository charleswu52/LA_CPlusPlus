cmake_minimum_required(VERSION 3.0.0)

project(LA VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(LA_C__ tests/entry.cpp LevenshteinDFA.cpp LevenshteinNFA.cpp Trie.cpp)