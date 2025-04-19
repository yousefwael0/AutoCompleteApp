# AutoCompleteApp

Auto-complete C++ application based on Trie Data Structure with file-based dictionary support.

## Features
- Autocomplete suggestions by prefix.
- Suggestions ordered by:
  - Word frequency (default)
  - Word length (shortest first)
  - Lexicographical order
- Add/Delete words from dictionary.
- Automatically track new words typed 3+ times.
- Case-insensitive matching.
- Highlight exact matches.
- Error handling for invalid inputs.

## Build Instructions

### Requirements
- C++ compiler supporting C++14 (g++, clang++, MSVC)
- CMake 3.10+
- SFML 3.0+ for GUI

### Build Steps

```bash
cd AutoCompleteApp
mkdir build
cd build
cmake ..
cmake --build .
./autocomplete