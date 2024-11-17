// main.cpp
#include "word_counter.h"
#include <iostream>


/*
JOEL REGI ABRAHAM
Parallel Computing Techniques
CSCN73000 - Fall 2024 - Section 2
Design Sprint
*/

int main() {
    const std::string filename = "Hamlet.txt";
    WordCounter counter(filename);

    
    counter.countWords();
    
    counter.printResults();

    return 0;
}