import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Basic


ApplicationWindow {
    visible: true
    width: 840
    height: 720
    title: "AutoComplete App"
    color: "#f7f9fb"
    font.family: "Arial"
    font.pixelSize: 16
    property string status: backend ? backend.statusMessage : "" // qmllint disable unqualified

    onClosing: {
        backend.saveData("../data/Dictionary.txt"); // qmllint disable unqualified
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        RowLayout {
            spacing: 10
            Layout.alignment: Qt.AlignRight

            Label {
                text: "Search Mode:"
                font.pixelSize: 14
                color: "#222"
            }

            ComboBox {
                id: modeSelector
                model: ["Most Frequent First", "Lexicographical", "Shortest First"]
                currentIndex: 0
                Layout.preferredWidth: 180
                font.pixelSize: 14

                // Customize dropdown list appearance
                delegate: ItemDelegate {
                    width: parent.width
                    background: Rectangle {
                        color: hovered ? "#e8f0fe" : "white" // qmllint disable unqualified
                        border.color: hovered ? "#3a86ff" : "transparent"
                    }
                    contentItem: Text {
                        text: modelData // qmllint disable unqualified
                        color: "#222"
                        font.pixelSize: 14
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                // Customize selected item display
                contentItem: Text {
                    text: modeSelector.displayText
                    font.pixelSize: 14
                    color: "#222"
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                    anchors.fill: parent
                    elide: Text.ElideRight
                }

                // Style the combo box background
                background: Rectangle {
                    color: "white"
                    border.color: modeSelector.focus ? "#3a86ff" : "#ccc"
                    border.width: 1
                    radius: 8
                }
                onCurrentIndexChanged: backend.handleInput(inputField.text, currentIndex) // qmllint disable unqualified
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextField {
                id: inputField
                placeholderText: "Type a word or prefix..."
                focus: true
                font.pixelSize: 16
                Layout.fillWidth: true
                leftPadding: 10
                rightPadding: 30
                color: "#222"
                placeholderTextColor: "#888"
                background: Rectangle {
                    color: "white"
                    radius: 8
                    border.color: inputField.activeFocus ? "#3a86ff" : "#ccc"
                    border.width: 1
                }

                onTextChanged: debounceTimer.restart()
                Timer {
                    id: debounceTimer
                    interval: 200
                    repeat: false
                    onTriggered: {
                        if (inputField.text.trim() !== "") {
                            backend.handleInput(inputField.text, modeSelector.currentIndex)
                        } else {
                            backend.clearStatus()
                            backend.clearSuggestions()
                        }
                    }
                }
                Keys.onPressed: event => {
                    if (event.key === Qt.Key_Down) {
                        if (suggestionView.count > 0)
                            suggestionView.currentIndex = (suggestionView.currentIndex + 1) % suggestionView.count
                        event.accepted = true
                    } else if (event.key === Qt.Key_Up) {
                        if (suggestionView.count > 0)
                            suggestionView.currentIndex = (suggestionView.currentIndex - 1 + suggestionView.count) % suggestionView.count
                        event.accepted = true
                    } else if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                        if (suggestionView.count > 0) {
                            inputField.text = suggestionView.model[suggestionView.currentIndex]
                            backend.handleInput(inputField.text, modeSelector.currentIndex) // qmllint disable unqualified
                            suggestionView.currentIndex = -1
                        }
                        event.accepted = true
                    }
                }
            }

            Button {
                text: "Add"
                font.pixelSize: 14
                background: Rectangle {
                    color: "#3a86ff"
                    radius: 8
                }
                contentItem: Text {
                    text: "Add"
                    color: "white"
                    font.pixelSize: 14
                    anchors.centerIn: parent
                }
                onClicked: backend.addNewWord(inputField.text) // qmllint disable unqualified
            }

            Button {
                text: "Delete"
                font.pixelSize: 14
                background: Rectangle {
                    color: "#ef233c"
                    radius: 8
                }
                contentItem: Text {
                    text: "Delete"
                    color: "white"
                    font.pixelSize: 14
                    anchors.centerIn: parent
                }
                onClicked: backend.deleteWord(inputField.text) // qmllint disable unqualified
            }
        }

        Label {
            text: status
            visible: status !== "" && inputField.text !== ""
            color: status.startsWith("Invalid") ? "#d90429"
                : status.startsWith("Word Deleted") ? "#d90429"
                : status.startsWith("New word") ? "#2b9348"
                : "#555"
            font.pixelSize: 14
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter

            Timer {
                id: statusClearTimer
                interval: 2500
                repeat: false
                onTriggered: backend.clearStatus()
            }

            Component.onCompleted: {
                if (status !== "")
                    statusClearTimer.start()
            }

            onTextChanged: function(newText) {
                if (newText !== "")
                    statusClearTimer.restart()
            }
        }

        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 8
            color: "white"
            border.color: "#ccc"
            border.width: 1

            ListView {
                id: suggestionView
                anchors.fill: parent
                model: backend ? backend.suggestions : [] // qmllint disable unqualified
                clip: true
                interactive: true
                currentIndex: 0
                focus: true

                delegate: Rectangle {
                    width: parent.width
                    height: 40
                    color: ListView.isCurrentItem ? "#e0f7fa" : hovered ? "#f1f1f1" : "white"
                    border.color: "#ddd"
                    radius: 4

                    property bool hovered: false

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.hovered = true
                        onExited: parent.hovered = false
                        onClicked: inputField.text = modelData // qmllint disable unqualified
                    }

                    Text {
                        anchors.centerIn: parent
                        text: modelData // qmllint disable unqualified
                        color: "#333"
                        font.pixelSize: 15
                    }
                }

                highlightFollowsCurrentItem: suggestionView.count > 0
            }

        }
    }
}
