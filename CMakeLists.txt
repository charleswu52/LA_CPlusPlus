cmake_minimum_required(VERSION 3.0.0)

project(levenshtein_automaton VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

aux_source_directory(src/levenshtein_automaton LEVENSHTEIN_AUTOMATON)

add_executable(test tests/test.cpp ${LEVENSHTEIN_AUTOMATON})

add_library(levenshtein_automaton ${LEVENSHTEIN_AUTOMATON})