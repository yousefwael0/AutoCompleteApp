#include "input_handler.h"

// Sanitizes input by converting to lowercase.
std::string InputHandler::sanitizeInput(const std::string& input)
{
    std::string result;
    for (char c : input)
    {
        result += tolower(c);
    }
    return result;
}

// Validates that the prefix contains only letters (a-z)
bool InputHandler::validatePrefix(const std::string& input)
{
    if (input.empty()) return false; //Reject empty input
    for (char c : input)
    {
        if (!isalpha(c)) return false;
    }
    return true;
}
