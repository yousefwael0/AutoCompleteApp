#include "trie.h"
#include <queue> // For BFS
#include <stack>

TrieNode::TrieNode() {
    // Initialize node
    isEndOfWord = false;
}

Trie::Trie() {
    // Initialize root
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    // Insert word into Trie
    TrieNode *temp = root;
    for (char c : word){
        if (temp->children.find(c) == temp->children.end()){
            temp->children[c] = new TrieNode();
        }
        temp = temp->children.at(c);
    }
    temp->isEndOfWord = true;
}

bool Trie::searchExact(const std::string& word) {
    // Return true if exact word exists
    TrieNode *temp = root;
    for (char c : word){
        if (temp->children.find(c) == temp->children.end()){
            return false;
        }
        temp = temp->children[c];
    }
    return true;
}

bool Trie::searchPrefix(const std::string& prefix) {
    // Return true if prefix exists
    TrieNode *temp = root;
    for (char c : prefix){
        if (temp->children.find(c) == temp->children.end()){
            return false;
        }
        temp = temp->children[c];
    }
    return true;
}

bool Trie::deleteWord(const std::string& word) {
    // Delete word from Trie
    TrieNode *node = root;
    std::stack<std::pair<TrieNode*, char>> s;
    for (char c : word){
        if (node->children.find(c) == node->children.end()){
            return false;
        }
        s.push({node, c});
        node = node->children[c];
    }
    if (!node->isEndOfWord){
        return false;
    }
    node->isEndOfWord = false;

    while (!s.empty()){
        TrieNode *parent = s.top().first;
        char c = s.top().second;
        TrieNode *child = parent->children[c];
        if (child->children.empty() && !child->isEndOfWord){
            delete child;
            parent->children.erase(c);
        } else{
            break;
        }
        s.pop();
    }
    return true;
}

void Trie::dfsHelper(TrieNode* node, std::string currentWord, std::vector<std::string>& results) {
    // Recursive DFS
    if (node->isEndOfWord == true){
        results.push_back(currentWord);
    }
    std::vector<char> keys;
    for (auto& child : node->children){
        keys.push_back(child.first);
    }
    std::sort(keys.begin(), keys.end());
    for (char c : keys){
        dfsHelper(node->children[c], currentWord + c, results);
    }
}

std::vector<std::string> Trie::getSuggestionsDFS(const std::string& prefix) {
    // Get words in lexicographical order
    std::vector<std::string> results;
    if (searchPrefix(prefix)){
        TrieNode *node = root;
        for (char c : prefix){
            node = node->children[c];
        }
        dfsHelper(node, prefix, results);
    }
    return results;
}

void Trie::bfsHelper(TrieNode* node, std::string prefix, std::vector<std::string>& results) {
    // BFS to find words (shortest first)
    std::queue<std::pair<TrieNode*, std::string>> q;
    q.push({node, prefix});
    
    while (!q.empty()){
        TrieNode *currNode = q.front().first;
        std::string currWord = q.front().second;
        q.pop();

        if (currNode->isEndOfWord){
            results.push_back(currWord);
        }

        for (auto& child : currNode->children){
            q.push({child.second, currWord + child.first});
        }
    }
}

std::vector<std::string> Trie::getSuggestionsBFS(const std::string& prefix) {
    // Get words in shortest length order
    std::vector<std::string> results;
    if (searchPrefix(prefix)){
        TrieNode *node = root;
        for (char c : prefix){
            node = node->children[c];
        }
        bfsHelper(node, prefix, results);
    }
    return results;
}