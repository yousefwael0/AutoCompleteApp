cmake_minimum_required(VERSION 3.10)
project(AutoCompleteApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all the source files
set(SOURCES
    src/main.cpp
    src/trie.cpp
    src/frequency_map.cpp
    src/file_io.cpp
    src/input_handler.cpp
    src/new_word_tracker.cpp
    src/ui.cpp
)

# Add include directories (if needed)
include_directories(src)

# Find SFML 3 components
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Create the executable
add_executable(autocomplete ${SOURCES})

# Link SFML libraries (note the case for SFML 3)
target_link_libraries(autocomplete SFML::Graphics SFML::Window SFML::System)