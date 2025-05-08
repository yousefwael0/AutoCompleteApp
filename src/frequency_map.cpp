#include "frequency_map.h"
#include <algorithm>
#include <iostream>

using namespace std;

FrequencyManager::FrequencyManager() {
    // Constructor - nothing to initialize manually
}

void FrequencyManager::addNewWord(const string& word) {
    // Already confirmed? Do nothing
    if (frequencyMap.find(word) != frequencyMap.end()) {
        cout << " Word already added";
        return;
    }
    frequencyMap[word] = 0;
}

void FrequencyManager::increaseFrequency(const string& word) {
    // Only increase if the word has been confirmed
    if (frequencyMap.find(word) != frequencyMap.end()) {
        frequencyMap[word]++;
    }
}

int FrequencyManager::getFrequency(const string& word) const {
    auto it = frequencyMap.find(word);
    if (it != frequencyMap.end()) {
        return it->second;
    }
    return 0;
}

void FrequencyManager::setFrequency(const string &word, int frequency){
    if(frequencyMap.find(word) != frequencyMap.end()){
        frequencyMap[word] = frequency;
    }
}

const unordered_map<string, int> &FrequencyManager::getMap() const{
    return frequencyMap;
}

vector<string> FrequencyManager::sortByFrequency(const vector<string>& words) const {
    vector<string> sortedWords = words;

    sort(sortedWords.begin(), sortedWords.end(), [this](const string& a, const string& b){
        return getFrequency(a) > getFrequency(b); // Descending
        });

    return sortedWords;
}
