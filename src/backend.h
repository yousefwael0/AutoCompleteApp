#pragma once

#include <QObject>
#include <QStringList>

#include "trie.h"
#include "file_io.h"
#include "input_handler.h"
#include "frequency_map.h"
#include "new_word_tracker.h"

class Backend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList suggestions READ suggestions NOTIFY suggestionsChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    bool loadData(const std::string &filename);
    Q_INVOKABLE void saveData(const QString &filename);
    Q_INVOKABLE void handleInput(const QString &text, int searchMode);
    Q_INVOKABLE void addNewWord(const QString &word);
    Q_INVOKABLE void deleteWord(const QString &word);
    Q_INVOKABLE void clearStatus();
    QStringList suggestions() const;
    QString statusMessage() const;

signals:
    void suggestionsChanged();
    void statusMessageChanged();

private:
    Trie trie;
    FileManager fileManager;
    InputHandler inputHandler;
    FrequencyManager freqManager;
    NewWordTracker newWordTracker;

    QStringList m_suggestions;
    QString m_statusMessage;
};
