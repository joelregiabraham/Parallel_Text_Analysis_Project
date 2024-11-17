// word_counter.cpp
#include "word_counter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <boost/thread.hpp>

WordCounter::WordCounter(const std::string& filename) : m_filename(filename) {}


/*
JOEL REGI ABRAHAM
Parallel Computing Techniques
CSCN73000 - Fall 2024 - Section 2
Design Sprint
*/

void WordCounter::countWords() {
    // Read the entire file content
    std::ifstream file(m_filename);
    if (!file) {
        std::cerr << "Error opening file: " << m_filename << std::endl;
        return;
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Divide the content into chunks
    std::vector<std::string> chunks = divideFileIntoChunks(content, NUM_THREADS);

    // Create and launch threads
    boost::thread_group threads;
    for (const auto& chunk : chunks) {
        threads.create_thread(boost::bind(&WordCounter::processChunk, this, chunk));
    }

    // Wait for all threads to complete
    threads.join_all();
}

void WordCounter::processChunk(const std::string& chunk) {
    std::istringstream iss(chunk);
    std::string word;
    while (iss >> word) {
        // Convert word to lowercase for case-insensitive comparison
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (word == "horatio") m_horatioCount++;
        else if (word == "and") m_andCount++;
        else if (word == "hamlet") m_hamletCount++;
        else if (word == "god") m_godCount++;

        m_totalWordCount++;
    }
}

std::vector<std::string> WordCounter::divideFileIntoChunks(const std::string& content, int numChunks) {
    std::vector<std::string> chunks;
    size_t chunkSize = content.size() / numChunks;
    size_t start = 0;

    for (int i = 0; i < numChunks - 1; ++i) {
        size_t end = start + chunkSize;
        // Adjust end to the next space to avoid splitting words
        while (end < content.size() && !std::isspace(content[end])) {
            ++end;
        }
        chunks.push_back(content.substr(start, end - start));
        start = end;
    }
    // Add the last chunk
    chunks.push_back(content.substr(start));

    return chunks;
}

void WordCounter::printResults() const {
    std::cout << m_horatioCount << " Horatio\n"
        << m_andCount << " and\n"
        << m_hamletCount << " Hamlet\n"
        << m_godCount << " God\n"
        << "Total word count = " << m_totalWordCount << std::endl;
}