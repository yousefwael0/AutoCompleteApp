#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class FrequencyManager {
private:
    std::unordered_map<std::string, int> frequencyMap;

public:
    FrequencyManager();
    void addNewWord(const std::string& word);
    void increaseFrequency(const std::string& word);
    int getFrequency(const std::string& word) const;
    std::vector<std::string> sortByFrequency(const std::vector<std::string>& words) const;
};