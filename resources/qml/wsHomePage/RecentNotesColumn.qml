import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../warningBox" as WarningBox

Rectangle {
    id: root
    color: "#161824"
    radius: 12
    border.color: Qt.rgba(1, 1, 1, 0.08)
    border.width: 1

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        // --- Column Header ---
        RowLayout {
            Layout.fillWidth: true

            Text {
                text: "Recent Notes"
                color: "#FFFFFF"
                font.pixelSize: 17
                font.bold: true
                font.family: "Inter"
            }

            Item { Layout.fillWidth: true }

            Rectangle {
                height: 22
                width: notesCountText.implicitWidth + 14
                radius: 11
                color: Qt.rgba(1, 1, 1, 0.06)

                Text {
                    id: notesCountText
                    anchors.centerIn: parent
                    text: (typeof wsHomePage !== "undefined" ? wsHomePage.recentNotes.length : 0) + " recent"
                    color: "#94A3B8"
                    font.pixelSize: 11
                    font.family: "Inter"
                }
            }
        }

        // --- Empty State ---
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: typeof wsHomePage !== "undefined" && wsHomePage.recentNotes.length === 0

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 12

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "📝"
                    font.pixelSize: 32
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "No notes yet in this workspace"
                    color: "#FFFFFF"
                    font.pixelSize: 14
                    font.bold: true
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Capture thoughts, specs, and meeting notes."
                    color: "#94A3B8"
                    font.pixelSize: 12
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    width: 120
                    height: 32
                    radius: 6
                    color: "#8B5CF6"

                    Text {
                        anchors.centerIn: parent
                        text: "+ New Note"
                        color: "#FFFFFF"
                        font.bold: true
                        font.pixelSize: 12
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            if (typeof wsHomePage !== "undefined") {
                                wsHomePage.createNewNote("Untitled Note")
                            }
                        }
                    }
                }
            }
        }

        // --- Notes Grid (Responsive 1 or 2 Columns without gaps) ---
        GridView {
            id: notesGrid
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            visible: typeof wsHomePage !== "undefined" && wsHomePage.recentNotes.length > 0

            readonly property bool isTwoCol: notesGrid.width >= 480
            cellWidth: isTwoCol ? Math.floor(notesGrid.width / 2) : notesGrid.width
            cellHeight: isTwoCol ? 142 : 110
            model: typeof wsHomePage !== "undefined" ? wsHomePage.recentNotes : []

            delegate: Item {
                width: notesGrid.cellWidth
                height: notesGrid.cellHeight

                Rectangle {
                    id: cardRect
                    anchors.fill: parent
                    anchors.margins: 5
                    radius: 10
                    color: cardMouse.containsMouse ? "#232637" : "#1B1D2B"
                    border.color: cardMouse.containsMouse ? Qt.rgba(1, 1, 1, 0.16) : Qt.rgba(1, 1, 1, 0.08)
                    border.width: 1

                    Behavior on color { ColorAnimation { duration: 120 } }
                    Behavior on border.color { ColorAnimation { duration: 120 } }

                    property string noteId: String(modelData.id || "")

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 11
                        spacing: 5

                        // --- Card Header: Title + Pin/Delete Actions ---
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 8

                            Text {
                                text: modelData.title || "Untitled Note"
                                font.pixelSize: 13
                                font.bold: true
                                color: "#FFFFFF"
                                elide: Text.ElideRight
                                Layout.fillWidth: true
                                font.family: "Inter"
                            }

                            // Pin icon button
                            Text {
                                text: modelData.isPinned ? "📌" : "☆"
                                font.pixelSize: 12
                                color: modelData.isPinned ? "#F59E0B" : "#94A3B8"
                                visible: modelData.isPinned || cardMouse.containsMouse

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        if (typeof wsHomePage !== "undefined" && cardRect.noteId) {
                                            wsHomePage.togglePinNote(cardRect.noteId)
                                        }
                                    }
                                }
                            }

                            // Delete button
                            Text {
                                text: "🗑"
                                font.pixelSize: 11
                                color: "#94A3B8"
                                visible: cardMouse.containsMouse

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        deleteDialog.noteIdToDelete = cardRect.noteId
                                        deleteDialog.visible = true
                                    }
                                }
                            }
                        }

                        // --- Card Body: Snippet Preview ---
                        Text {
                            text: (typeof modelData.preview === "string" && modelData.preview.trim().length > 0)
                                ? modelData.preview
                                : "No additional text"
                            font.pixelSize: 11
                            color: "#94A3B8"
                            wrapMode: Text.Wrap
                            elide: Text.ElideRight
                            maximumLineCount: notesGrid.isTwoCol ? 2 : 1
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            font.family: "Inter"
                        }

                        // --- Card Footer: Project Badge, Time, Word Count ---
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 8

                            // Project Badge Pill
                            Rectangle {
                                visible: modelData.projectName !== ""
                                height: 18
                                width: projText.implicitWidth + 10
                                radius: 4
                                color: Qt.rgba(0.55, 0.36, 0.96, 0.14)

                                Text {
                                    id: projText
                                    anchors.centerIn: parent
                                    text: modelData.projectName
                                    font.pixelSize: 9
                                    color: modelData.projectColor !== "" ? modelData.projectColor : "#A78BFA"
                                    font.weight: Font.DemiBold
                                }
                            }

                            Text {
                                text: modelData.updatedAtFormatted || ""
                                font.pixelSize: 10
                                color: "#64748B"
                                font.family: "Inter"
                            }

                            Item { Layout.fillWidth: true }

                            Text {
                                text: modelData.wordCountFormatted || ""
                                font.pixelSize: 10
                                color: "#64748B"
                                font.family: "Inter"
                            }
                        }
                    }

                    // Click card to open note
                    MouseArea {
                        id: cardMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        z: -1
                        onClicked: {
                            if (typeof wsHomePage !== "undefined" && cardRect.noteId) {
                                wsHomePage.openNote(cardRect.noteId)
                            }
                        }
                    }
                }
            }
        }
    }

    // Delete Confirmation Dialog
    Popup {
        id: deleteDialog
        modal: true
        parent: Overlay.overlay
        anchors.centerIn: parent
        width: 480
        height: 190
        padding: 0

        Overlay.modal: Rectangle {
            color: Qt.rgba(0, 0, 0, 0.6)
        }

        property string noteIdToDelete: ""

        WarningBox.NoteDeletion {
            anchors.fill: parent
            onConfirmDelete: {
                if (typeof wsHomePage !== "undefined" && deleteDialog.noteIdToDelete) {
                    wsHomePage.deleteNote(deleteDialog.noteIdToDelete)
                }
                deleteDialog.visible = false
            }
            onCancel: {
                deleteDialog.visible = false
            }
        }
    }
}
