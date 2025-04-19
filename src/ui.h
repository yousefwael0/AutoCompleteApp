#pragma once
#include <vector>
#include <string>
#include "frequency_map.h"

class UI {
public:
    static void displaySuggestions(const std::vector<std::string>& suggestions, const std::string& prefix, const FrequencyManager& freqManager);
};