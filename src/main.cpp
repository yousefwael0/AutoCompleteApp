#include <iostream>
#include <string>
#include "trie.h"
#include "frequency_map.h"
#include "file_io.h"
#include "input_handler.h"
#include "new_word_tracker.h"
#include "ui.h"

Trie trie;
FrequencyManager freqManager;
FileManager fileManager;
InputHandler inputHandler;
NewWordTracker newWordTracker;

int main() {
    // 1. Load data once from file
    if (!fileManager.loadData("data/Dictionary.txt", trie, freqManager)) {
        std::cout << "Failed to load dictionary file. Exiting.\n";
        return 1;
    }

    std::cout << "Welcome to the AutoComplete App!\n";
    std::cout << "Type 'exit' anytime to quit.\n";

    std::string input;

    while (true) {
        std::cout << "\nEnter a word or prefix: ";
        std::getline(std::cin, input);

        // 2. Input handling
        input = inputHandler.sanitizeInput(input);

        if (input == "exit")
            break;

        if (!inputHandler.validatePrefix(input)) {
            std::cout << "Invalid input! Please enter letters only.\n";
            continue;
        }

        // 3. Search Trie
        if (trie.searchPrefix(input)) {
            std::vector<std::string> suggestions = trie.getSuggestionsDFS(input); // or BFS based on user setting
            UI::displaySuggestions(suggestions, input, freqManager);

            // 4. If exact match (user typed a full word that exists)
            if (trie.searchExact(input)) {
                freqManager.increaseFrequency(input);
            }
        }
        else {
            std::cout << "No suggestions found for '" << input << "'.\n";
            newWordTracker.recordNewWord(input, trie, freqManager);
        }
    }

    // 5. Save updated data before exiting
    fileManager.saveData("data/Dictionary.txt", freqManager);

    std::cout << "Data saved. Goodbye!\n";
    return 0;
}