import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    implicitHeight: mainLayout.implicitHeight
    Layout.fillWidth: true

    readonly property bool isCompact: root.width < 760
    readonly property bool isNarrowCards: root.width < 880

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        spacing: 16

        // =========================================================
        // TOP ROW: Responsive Branding / Greeting & Actions
        // =========================================================
        GridLayout {
            Layout.fillWidth: true
            columns: root.isCompact ? 1 : 2
            rowSpacing: 12
            columnSpacing: 16

            // --- Branding & Greeting ---
            RowLayout {
                Layout.fillWidth: true
                spacing: 14
                Layout.alignment: Qt.AlignVCenter

                // ChronoTasks Logo Mark
                Rectangle {
                    width: 38
                    height: 38
                    radius: 10
                    color: "transparent"

                    Image {
                        anchors.fill: parent
                        source: "qrc:/icons/chronotasks_logo.svg"
                        sourceSize.width: 38
                        sourceSize.height: 38
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                    }
                }

                ColumnLayout {
                    spacing: 2
                    Layout.fillWidth: true

                    RowLayout {
                        spacing: 8
                        Layout.fillWidth: true

                        Text {
                            text: "Welcome back, " + (typeof wsHomePage !== "undefined" ? wsHomePage.workspaceName : "Personal Workspace")
                            color: "#FFFFFF"
                            font.pixelSize: root.isCompact ? 19 : 22
                            font.bold: true
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.maximumWidth: root.isCompact ? root.width - 70 : 450
                        }

                        // Project badge if available
                        Rectangle {
                            visible: typeof wsHomePage !== "undefined" && wsHomePage.activeProjectName !== "" && wsHomePage.activeProjectName !== "General"
                            height: 20
                            width: activeProjText.implicitWidth + 12
                            radius: 10
                            color: Qt.rgba(0.55, 0.36, 0.96, 0.15)
                            border.color: Qt.rgba(0.55, 0.36, 0.96, 0.35)
                            border.width: 1

                            Text {
                                id: activeProjText
                                anchors.centerIn: parent
                                text: typeof wsHomePage !== "undefined" ? wsHomePage.activeProjectName : ""
                                color: "#C4B5FD"
                                font.pixelSize: 10
                                font.weight: Font.DemiBold
                            }
                        }
                    }

                    // Live Date & Time Widget
                    RowLayout {
                        spacing: 8

                        Text {
                            id: dateTimeDisplay
                            text: Qt.formatDateTime(new Date(), "dddd, MMMM d, yyyy | h:mm AP")
                            color: "#94A3B8"
                            font.pixelSize: 12
                            font.family: "Inter"
                        }

                        Timer {
                            interval: 10000
                            running: true
                            repeat: true
                            onTriggered: {
                                dateTimeDisplay.text = Qt.formatDateTime(new Date(), "dddd, MMMM d, yyyy | h:mm AP")
                            }
                        }
                    }
                }
            }

            // --- Top Action Buttons ---
            RowLayout {
                Layout.alignment: root.isCompact ? Qt.AlignLeft : Qt.AlignRight
                spacing: 8

                // PRIMARY BUTTON: + New Task
                Button {
                    id: btnNewTask
                    text: "+ New Task"
                    onClicked: {
                        if (typeof wsHomePage !== "undefined") {
                            wsHomePage.createNewTask("Untitled Task")
                        }
                    }

                    contentItem: RowLayout {
                        spacing: 6
                        anchors.centerIn: parent
                        Text {
                            text: "+"
                            color: "#FFFFFF"
                            font.pixelSize: 15
                            font.bold: true
                        }
                        Text {
                            text: "New Task"
                            color: "#FFFFFF"
                            font.pixelSize: 12
                            font.weight: Font.DemiBold
                            font.family: "Inter"
                        }
                    }

                    background: Rectangle {
                        implicitWidth: root.isCompact ? 110 : 120
                        implicitHeight: 36
                        radius: 8
                        color: btnNewTask.down ? "#6D28D9" : (btnNewTask.hovered ? "#7C3AED" : "#8B5CF6")
                        Behavior on color { ColorAnimation { duration: 120 } }
                    }
                }

                // SECONDARY BUTTON: + New Note
                Button {
                    id: btnNewNote
                    text: "+ New Note"
                    onClicked: {
                        if (typeof wsHomePage !== "undefined") {
                            wsHomePage.createNewNote("Untitled Note")
                        }
                    }

                    contentItem: RowLayout {
                        spacing: 6
                        anchors.centerIn: parent
                        Text {
                            text: "📄"
                            font.pixelSize: 11
                        }
                        Text {
                            text: "New Note"
                            color: "#E2E8F0"
                            font.pixelSize: 12
                            font.weight: Font.Medium
                            font.family: "Inter"
                        }
                    }

                    background: Rectangle {
                        implicitWidth: root.isCompact ? 106 : 116
                        implicitHeight: 36
                        radius: 8
                        color: btnNewNote.down ? "#161824" : (btnNewNote.hovered ? "#26293A" : "#1C1E2B")
                        border.color: btnNewNote.hovered ? "#474D67" : "#2E3245"
                        border.width: 1
                        Behavior on color { ColorAnimation { duration: 120 } }
                        Behavior on border.color { ColorAnimation { duration: 120 } }
                    }
                }

                // SECONDARY BUTTON: Upload File
                Button {
                    id: btnUploadFile
                    text: "Upload File"
                    onClicked: {
                        if (typeof wsHomePage !== "undefined") {
                            wsHomePage.openUploadDialog()
                        }
                    }

                    contentItem: RowLayout {
                        spacing: 6
                        anchors.centerIn: parent
                        Text {
                            text: "📤"
                            font.pixelSize: 11
                        }
                        Text {
                            text: "Upload"
                            color: "#E2E8F0"
                            font.pixelSize: 12
                            font.weight: Font.Medium
                            font.family: "Inter"
                        }
                    }

                    background: Rectangle {
                        implicitWidth: root.isCompact ? 96 : 106
                        implicitHeight: 36
                        radius: 8
                        color: btnUploadFile.down ? "#161824" : (btnUploadFile.hovered ? "#26293A" : "#1C1E2B")
                        border.color: btnUploadFile.hovered ? "#474D67" : "#2E3245"
                        border.width: 1
                        Behavior on color { ColorAnimation { duration: 120 } }
                        Behavior on border.color { ColorAnimation { duration: 120 } }
                    }
                }
            }
        }

        // =========================================================
        // KPI SUMMARY STATS CARDS GRID (Responsive 2 or 4 Columns)
        // =========================================================
        GridLayout {
            Layout.fillWidth: true
            columns: root.isNarrowCards ? 2 : 4
            rowSpacing: 10
            columnSpacing: 12

            // --- Card 1: Tasks Due Today ---
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 82
                radius: 12
                color: "#181A26"
                border.color: Qt.rgba(1, 1, 1, 0.07)
                border.width: 1

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 12

                    Rectangle {
                        width: 40
                        height: 40
                        radius: 10
                        color: Qt.rgba(0.55, 0.36, 0.96, 0.16)

                        Text {
                            anchors.centerIn: parent
                            text: "⏱"
                            font.pixelSize: 18
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 2

                        Text {
                            text: (typeof wsHomePage !== "undefined" ? wsHomePage.tasksDueTodayCount : 0) + " Tasks Today"
                            color: "#FFFFFF"
                            font.pixelSize: 15
                            font.bold: true
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }

                        Text {
                            text: typeof wsHomePage !== "undefined"
                                ? (wsHomePage.tasksRemainingCount > 0 ? (wsHomePage.tasksRemainingCount + " remaining") : "All completed")
                                : "0 remaining"
                            color: "#94A3B8"
                            font.pixelSize: 11
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }
                }
            }

            // --- Card 2: Active Projects ---
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 82
                radius: 12
                color: "#181A26"
                border.color: Qt.rgba(1, 1, 1, 0.07)
                border.width: 1

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 12

                    Rectangle {
                        width: 40
                        height: 40
                        radius: 10
                        color: Qt.rgba(0.23, 0.51, 0.96, 0.16)

                        Text {
                            anchors.centerIn: parent
                            text: "📁"
                            font.pixelSize: 18
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 2

                        Text {
                            text: (typeof wsHomePage !== "undefined" ? wsHomePage.activeProjectsCount : 0) + " Projects"
                            color: "#FFFFFF"
                            font.pixelSize: 15
                            font.bold: true
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Active in workspace"
                            color: "#94A3B8"
                            font.pixelSize: 11
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }
                }
            }

            // --- Card 3: Total Notes ---
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 82
                radius: 12
                color: "#181A26"
                border.color: Qt.rgba(1, 1, 1, 0.07)
                border.width: 1

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 12

                    Rectangle {
                        width: 40
                        height: 40
                        radius: 10
                        color: Qt.rgba(0.06, 0.72, 0.51, 0.16)

                        Text {
                            anchors.centerIn: parent
                            text: "📝"
                            font.pixelSize: 18
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 2

                        Text {
                            text: (typeof wsHomePage !== "undefined" ? wsHomePage.totalNotesCount : 0) + " Notes"
                            color: "#FFFFFF"
                            font.pixelSize: 15
                            font.bold: true
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }

                        Text {
                            text: "Workspace library"
                            color: "#94A3B8"
                            font.pixelSize: 11
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }
                }
            }

            // --- Card 4: Velocity / Completion ---
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 82
                radius: 12
                color: "#181A26"
                border.color: Qt.rgba(1, 1, 1, 0.07)
                border.width: 1

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 12

                    Rectangle {
                        width: 40
                        height: 40
                        radius: 10
                        color: Qt.rgba(0.96, 0.62, 0.04, 0.16)

                        Text {
                            anchors.centerIn: parent
                            text: "⚡"
                            font.pixelSize: 18
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 2

                        Text {
                            text: (typeof wsHomePage !== "undefined" ? wsHomePage.completionPercentage : 0) + "% Done"
                            color: "#FFFFFF"
                            font.pixelSize: 15
                            font.bold: true
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }

                        Text {
                            text: (typeof wsHomePage !== "undefined" && wsHomePage.completionPercentage >= 80) ? "High velocity" : "In progress"
                            color: "#94A3B8"
                            font.pixelSize: 11
                            font.family: "Inter"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }
}
