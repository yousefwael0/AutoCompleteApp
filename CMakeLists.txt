cmake_minimum_required(VERSION 3.16)
project(AutoCompleteApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

# Find Qt
find_package(Qt6 REQUIRED COMPONENTS Gui Qml Quick)

# Add your source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/trie.cpp
    src/frequency_map.cpp
    src/file_io.cpp
    src/input_handler.cpp
    src/new_word_tracker.cpp
    src/backend.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Gui Qt6::Qml Qt6::Quick)

# If you're using Qt's resource system (optional):
qt_add_resources(${PROJECT_NAME} "qml_resources"
    PREFIX "/"
    FILES qml/ui.qml
)