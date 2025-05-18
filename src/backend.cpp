#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent) {}

bool Backend::loadData(const std::string &filename) {
    return fileManager.loadData(filename, trie, freqManager);
}

void Backend::saveData(const QString &filename)
{
    fileManager.saveData(filename.toStdString(), freqManager);
}

void Backend::handleInput(const QString &text, int searchMode) {
    std::string input = inputHandler.sanitizeInput(text.toStdString());

    if (input.empty()) {
        // Clear suggestions and status for empty input, no error message
        emit suggestionsChanged();
        emit statusMessageChanged();
        return;
    }

    m_suggestions.clear();
    m_statusMessage.clear();

    if (!inputHandler.validatePrefix(input)) {
        m_statusMessage = "Invalid input! Letters only.";
    } else if (trie.searchPrefix(input)) {
        std::vector<std::string> raw;
        if (searchMode == 1){
            raw = trie.getSuggestionsDFS(input);
        }else if (searchMode == 2){
            raw = trie.getSuggestionsBFS(input);
        }else{
            raw = freqManager.sortByFrequency(trie.getSuggestionsBFS(input));
        }
        for (const auto &s : raw) {
            m_suggestions << QString::fromStdString(s);
        }

        if (trie.searchExact(input)) {
            freqManager.increaseFrequency(input);
        }
    } else {
        m_statusMessage = "No suggestions found.";
        newWordTracker.recordNewWord(input, trie, freqManager);
    }

    emit suggestionsChanged();
    emit statusMessageChanged();
}

void Backend::addNewWord(const QString &word) {
    std::string input = inputHandler.sanitizeInput(word.toStdString());

    if (!inputHandler.validatePrefix(input)) {
        m_statusMessage.clear();
        m_statusMessage = "Invalid word! Letters only.";
    } else {
        m_suggestions.clear();
        freqManager.addNewWord(input);
        trie.insert(input);
        m_statusMessage = "New word added: " + QString::fromStdString(input);
    }

    emit suggestionsChanged();
    emit statusMessageChanged();
}

void Backend::deleteWord(const QString &word)
{
    std::string input = inputHandler.sanitizeInput(word.toStdString());

    if (!inputHandler.validatePrefix(input)) {
        m_statusMessage.clear();
        m_statusMessage = "Invalid word! Letters only.";
    } else {
        m_statusMessage.clear();
        freqManager.deleteWord(input);
        trie.deleteWord(input);
        m_statusMessage = "Word Deleted: " + QString::fromStdString(input);
    }

    emit suggestionsChanged();
    emit statusMessageChanged();
}

void Backend::clearStatus()
{
    m_statusMessage.clear();
    emit statusMessageChanged();
}

void Backend::clearSuggestions(){
    m_suggestions.clear();
    emit suggestionsChanged();
}

QStringList Backend::suggestions() const {
    return m_suggestions;
}

QString Backend::statusMessage() const
{
    return m_statusMessage;
}

