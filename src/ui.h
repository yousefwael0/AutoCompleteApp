#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QListWidget>
#include <QStringList>
#include "frequency_map.h"

class UI : public QMainWindow {
    Q_OBJECT

public:
    UI(QWidget* parent = nullptr);
    ~UI();

private slots:
    void onTextChanged(const QString& text);

private:
    QLineEdit* inputField;
    QListWidget* suggestionList;

    FrequencyManager* freqManager; // Pointer to your frequency manager (passed externally or initialized)
    
    void updateSuggestions(const QString& prefix);
};