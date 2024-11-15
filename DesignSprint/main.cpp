// main.cpp
#include "word_counter.h"
#include <iostream>

int main() {
    const std::string filename = "Hamlet.txt";
    WordCounter counter(filename);

    std::cout << "Starting word count analysis..." << std::endl;
    counter.countWords();
    std::cout << "Analysis complete. Results:" << std::endl;
    counter.printResults();

    return 0;
}