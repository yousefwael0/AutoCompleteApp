#pragma once
#include <unordered_map>
#include <string>
#include "trie.h"
#include "frequency_map.h"

class NewWordTracker {
private:
    std::unordered_map<std::string, int> newWordsCount;

public:
    void recordNewWord(const std::string& word, Trie& trie, FrequencyManager& freqManager);
};