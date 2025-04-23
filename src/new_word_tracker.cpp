#include "new_word_tracker.h"
#include <algorithm>
#include <iostream>

using namespace std;


void NewWordTracker::recordNewWord(const string& word, Trie& trie, FrequencyManager& freqManager) {
    // Track word frequency
    // If word typed 3 times, insert into Trie and FrequencyManager

    if (word.empty()) { return; }

    string lowerWord;
    lowerWord.reserve(word.size());
    transform(word.begin(), word.end(), back_inserter(lowerWord), tolower);

    if (trie.searchExact(lowerWord)) { return; }

    int currentCount = ++newWordsCount[lowerWord];

    if (currentCount == INSERT_THRESHOLD) {
        trie.insert(lowerWord);
        freqManager.addNewWord(lowerWord);
        freqManager.increaseFrequency(lowerWord);
        newWordsCount.erase(lowerWord);
    }
}

