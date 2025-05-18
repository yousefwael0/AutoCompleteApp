#include "file_io.h"
#include <fstream>
#include <sstream>

using namespace std;

// Open file and load into Trie and FrequencyManager
bool FileManager::loadData(const string& filename, Trie& trie, FrequencyManager& freqManager){
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

        trie.insert(word);
        freqManager.addNewWord(word);

        freqManager.setFrequency(word, frequency);
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