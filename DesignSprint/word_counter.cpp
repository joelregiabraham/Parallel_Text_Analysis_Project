// word_counter.cpp
#include "word_counter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>


/*
JOEL REGI ABRAHAM
Parallel Computing Techniques
CSCN73000 - Fall 2024 - Section 2
Design Sprint
*/


WordCounter::WordCounter(const std::string& filename) : m_filename(filename) {}

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

    // Step 1: Count specific words
    boost::thread_group threads;
    for (const auto& chunk : chunks) {
        threads.create_thread(boost::bind(&WordCounter::countSpecificWords, this, chunk));
    }
    threads.join_all();

    // Step 2: Count total words using Thread Pool
    boost::asio::thread_pool pool(NUM_THREADS);
    for (const auto& chunk : chunks) {
        boost::asio::post(pool, boost::bind(&WordCounter::countTotalWords, this, chunk));
    }
    pool.join();
}

void WordCounter::countSpecificWords(const std::string& chunk) {
    std::istringstream iss(chunk);
    std::string word;
    while (iss >> word) {
        // Remove punctuation and convert to lowercase
        std::string clean_word = boost::algorithm::to_lower_copy(word);
        boost::algorithm::trim_if(clean_word, boost::is_any_of(".,!?:;\"'()[]{}"));

        if (clean_word == "horatio") m_horatioCount++;
        else if (clean_word == "and") m_andCount++;
        else if (clean_word == "hamlet") m_hamletCount++;
        else if (clean_word == "god") m_godCount++;
    }
}

void WordCounter::countTotalWords(const std::string& chunk) {
    std::istringstream iss(chunk);
    std::string word;
    while (iss >> word) {
        // Count any non-empty string as a word
        if (!word.empty()) {
            m_totalWordCount++;
        }
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