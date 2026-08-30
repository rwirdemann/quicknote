import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import Quicknote

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: false
    title: "Tagesnotiz — " + note.filePath
    color: "#1a1b26"
    flags: Qt.Window | Qt.FramelessWindowHint

    // Tokyo Night palette
    readonly property color tnBg: "#1a1b26"
    readonly property color tnBgDark: "#16161e"
    readonly property color tnBgHighlight: "#24283b"
    readonly property color tnFg: "#d6dbf5"
    readonly property color tnComment: "#565f89"
    readonly property color tnBlue: "#7aa2f7"
    readonly property color tnOrange: "#ff9e64"
    readonly property color tnSelection: "#283457"

    DailyNote {
        id: note
    }

    Shortcut {
        sequence: StandardKey.Save
        onActivated: note.save()
    }

    onClosing: note.save()

    GlobalHotkey {
        onActivated: {
            window.show()
            window.raise()
            window.requestActivate()
        }
    }

    MenuBar {
        Menu {
            title: "Datei"

            MenuItem {
                role: MenuItem.QuitRole
                text: "Fenster schließen"
                shortcut: StandardKey.Quit
                onTriggered: {
                    note.save()
                    window.hide()
                }
            }
        }
    }

    SystemTrayIcon {
        id: trayIcon
        visible: true
        icon.source: "qrc:/qt/qml/Quicknote/resources/tray-icon.png"
        icon.mask: true

        onActivated: reason => {
            if (reason !== SystemTrayIcon.Trigger)
                return

            if (window.visible) {
                note.save()
                window.hide()
            } else {
                window.show()
                window.raise()
                window.requestActivate()
            }
        }
    }

    header: ToolBar {
        id: titleBar
        background: Rectangle { color: window.tnBgHighlight }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onPressed: window.startSystemMove()
        }

    }

    ScrollView {
        anchors.fill: parent

        TextArea {
            id: editor
            text: note.content
            wrapMode: TextArea.Wrap
            font.family: "JetBrainsMono Nerd Font Mono"
            font.pixelSize: 13
            selectByMouse: true
            padding: 12

            color: window.tnFg
            selectionColor: window.tnSelection
            selectedTextColor: window.tnFg

            background: Rectangle { color: window.tnBg }

            onTextChanged: {
                if (note.content !== text)
                    note.content = text
            }
        }
    }

    footer: ToolBar {
        implicitHeight: 32
        background: Rectangle { color: window.tnBgDark }

        RowLayout {
            anchors.fill: parent
            anchors.margins: 8

            Label {
                text: note.status
                color: window.tnComment
                Layout.fillWidth: true
            }

            Label {
                text: note.dirty ? "●" : ""
                color: window.tnOrange
            }
        }
    }
}
