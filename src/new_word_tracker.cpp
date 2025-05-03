#include "new_word_tracker.h"
#include <algorithm>
#include <iostream>

using namespace std;


void NewWordTracker::recordNewWord(const string& word, Trie& trie, FrequencyManager& freqManager) {
    // Track word frequency
    // If word typed 3 times, insert into Trie and FrequencyManager

    if (word.empty()) { return; }

    if (trie.searchExact(word)) { return; }

    int currentCount = ++newWordsCount[word];

    if (currentCount == INSERT_THRESHOLD) {
        trie.insert(word);
        freqManager.addNewWord(word);
        freqManager.increaseFrequency(word);
        newWordsCount.erase(word);
    }
}

