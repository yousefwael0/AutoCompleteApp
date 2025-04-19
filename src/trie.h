#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class TrieNode {
public:
    bool isEndOfWord;
    std::unordered_map<char, TrieNode*> children;

    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    void dfsHelper(TrieNode* node, std::string currentWord, std::vector<std::string>& results);
    void bfsHelper(TrieNode* node, std::string prefix, std::vector<std::string>& results);

public:
    Trie();
    void insert(const std::string& word);
    bool searchExact(const std::string& word);
    bool searchPrefix(const std::string& prefix);
    bool deleteWord(const std::string& word);
    std::vector<std::string> getSuggestionsDFS(const std::string& prefix);
    std::vector<std::string> getSuggestionsBFS(const std::string& prefix);
};