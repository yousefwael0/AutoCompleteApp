#include "file_io.h"
#include <fstream>
#include <sstream>
#iclude <algorithm>
#iclude <cctype>  //for toLower()

using namespace std;

// Convert string to lowercase using <algorithm> (transform())
string toLower(const string& str) {
    string lowered = str;
    transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
    return lowered;

bool FileManager::loadData(const string& filename, Trie& trie, FrequencyManager& freqManager) {// Open file and load into Trie and FrequencyManager
    
    ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string word;
        int frequency;

        if (!(iss >> word >> frequency)) {
            continue; // skip malformed lines
        }

        word = toLower(word); // ensure case insensitivity

        trie.insert(word);

        for (int i = 0; i < frequency; ++i) {
            freqManager.increaseFrequency(word);
        }
    }

    infile.close();
    return true;
}


void FileManager::saveData(const string& filename, const FrequencyManager& freqManager) {// Save frequency map back to file
    
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        return;
    }

    const auto& freqMap = freqManager.getMap();  //add getMap() method to freq class
    for (const auto& pair : freqMap) {
        outfile << pair.first << " " << pair.second << endl;
    }

    outfile.close();

}
#include "file_io.h"
#include <fstream>
#include <sstream>
#iclude <algorithm>
#iclude <cctype>  //for toLower()

using namespace std;

// Convert string to lowercase using <algorithm> (transform())
string toLower(const string& str) {
    string lowered = str;
    transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
    return lowered;

bool FileManager::loadData(const string& filename, Trie& trie, FrequencyManager& freqManager) {// Open file and load into Trie and FrequencyManager
    
    ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string word;
        int frequency;

        if (!(iss >> word >> frequency)) {
            continue; // skip malformed lines
        }

        word = toLower(word); // ensure case insensitivity

        trie.insert(word);

        for (int i = 0; i < frequency; ++i) {
            freqManager.increaseFrequency(word);
        }
    }

    infile.close();
    return true;
}


void FileManager::saveData(const string& filename, const FrequencyManager& freqManager) {// Save frequency map back to file
    
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        return;
    }

    const auto& freqMap = freqManager.getMap();  //add getMap() method to freq class
    for (const auto& pair : freqMap) {
        outfile << pair.first << " " << pair.second << endl;
    }

    outfile.close();

}