#include "FrequencyManager.h"
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
    // If in pending, increment counter
    if (pendingMap.find(word) != pendingMap.end()) {
        pendingMap[word]++;

        // Promote to confirmed if it hits 3
        if (pendingMap[word] >= 3) {
            frequencyMap[word] = 0;
            pendingMap.erase(word);
        }
    }
    else {
        // Brand new word, add to pending with 1 count
        pendingMap[word] = 1;
    }
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

vector<string> FrequencyManager::sortByFrequency(const vector<string>& words) const {
    vector<string> sortedWords = words;

    sort(sortedWords.begin(), sortedWords.end(), [this](const string& a, const string& b) {
        return getFrequency(a) > getFrequency(b); // Descending
        });

    return sortedWords;
}
