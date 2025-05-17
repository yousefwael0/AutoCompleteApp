#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class FrequencyManager {
private:
    unordered_map<string, int> frequencyMap;  // Confirmed words + frequency

public:
    FrequencyManager();
    void addNewWord(const string& word); // Adds new or updates pending
    void deleteWord(const string& word); // Deleted a word
    void increaseFrequency(const string& word); // Only increases if in confirmed map
    int getFrequency(const string& word) const; // Returns 0 if not in confirmed
    void setFrequency(const string& word, int frequency);
    const unordered_map<string, int> &getMap() const;
    vector<string> sortByFrequency(const vector<string>& words) const;  // Sort words by freq
};
