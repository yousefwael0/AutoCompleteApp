#pragma once
#include <string>
#include <cctype>

class InputHandler 
{
public:
    // Core validation.
    std::string sanitizeInput(const std::string& input);
    bool validatePrefix(const std::string& prefix);
};