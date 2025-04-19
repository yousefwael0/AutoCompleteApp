#pragma once
#include <string>

class InputHandler {
public:
    std::string sanitizeInput(const std::string& input);
    bool validatePrefix(const std::string& input);
};