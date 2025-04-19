#pragma once
#include "trie.h"
#include "frequency_map.h"
#include <string>

class FileManager {
public:
    bool loadData(const std::string& filename, Trie& trie, FrequencyManager& freqManager);
    void saveData(const std::string& filename, const FrequencyManager& freqManager);
};