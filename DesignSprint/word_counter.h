// word_counter.h
#pragma once

#include <string>
#include <atomic>
#include <vector>
#include <boost/thread.hpp>

/*
JOEL REGI ABRAHAM
Parallel Computing Techniques
CSCN73000 - Fall 2024 - Section 2
Design Sprint
*/

class WordCounter {
public:
    WordCounter(const std::string& filename);
    void countWords();
    void printResults() const;

private:
    void processChunk(const std::string& chunk);
    std::vector<std::string> divideFileIntoChunks(const std::string& content, int numChunks);

    std::string m_filename;
    std::atomic<int> m_horatioCount{ 0 };
    std::atomic<int> m_andCount{ 0 };
    std::atomic<int> m_hamletCount{ 0 };
    std::atomic<int> m_godCount{ 0 };
    std::atomic<int> m_totalWordCount{ 0 };

    static const int NUM_THREADS = 4;
};