import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "#161824"
    radius: 12
    border.color: Qt.rgba(1, 1, 1, 0.08)
    border.width: 1

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 18
        spacing: 14

        // --- Column Header ---
        RowLayout {
            Layout.fillWidth: true

            Text {
                text: "Today's Focus"
                color: "#FFFFFF"
                font.pixelSize: 18
                font.bold: true
                font.family: "Inter"
            }

            Item { Layout.fillWidth: true }

            Rectangle {
                height: 22
                width: taskCountText.implicitWidth + 14
                radius: 11
                color: Qt.rgba(1, 1, 1, 0.06)

                Text {
                    id: taskCountText
                    anchors.centerIn: parent
                    text: (typeof wsHomePage !== "undefined" ? wsHomePage.tasksRemainingCount : 0) + " due"
                    color: "#94A3B8"
                    font.pixelSize: 11
                    font.family: "Inter"
                }
            }
        }

        // --- Overdue Alert Banner (if any overdue) ---
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 32
            radius: 6
            color: Qt.rgba(0.94, 0.27, 0.27, 0.12)
            border.color: Qt.rgba(0.94, 0.27, 0.27, 0.3)
            border.width: 1
            visible: typeof wsHomePage !== "undefined" && wsHomePage.overdueTasks.length > 0

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 8

                Text {
                    text: "⚠️"
                    font.pixelSize: 12
                }

                Text {
                    text: (typeof wsHomePage !== "undefined" ? wsHomePage.overdueTasks.length : 0) + " overdue tasks need attention"
                    color: "#FCA5A5"
                    font.pixelSize: 11
                    font.bold: true
                    font.family: "Inter"
                    Layout.fillWidth: true
                }
            }
        }

        // --- Task List View ---
        ListView {
            id: taskListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 8
            clip: true
            model: typeof wsHomePage !== "undefined" ? wsHomePage.todayTasks : []

            visible: typeof wsHomePage !== "undefined" && wsHomePage.todayTasks.length > 0

            delegate: Rectangle {
                id: taskItemRect
                width: taskListView.width
                height: 56
                radius: 8
                color: taskMouse.containsMouse ? "#232637" : "#1B1D2B"
                border.color: taskMouse.containsMouse ? Qt.rgba(1, 1, 1, 0.16) : Qt.rgba(1, 1, 1, 0.06)
                border.width: 1

                Behavior on color { ColorAnimation { duration: 120 } }
                Behavior on border.color { ColorAnimation { duration: 120 } }

                property string taskId: String(modelData.id || "")
                property bool isDone: Boolean(modelData.isCompleted)
                property string priorityLevel: String(modelData.priority || "Medium")

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 12

                    // Checkbox
                    Rectangle {
                        width: 20
                        height: 20
                        radius: 5
                        color: taskItemRect.isDone ? "#10B981" : "transparent"
                        border.color: taskItemRect.isDone ? "#10B981" : (checkArea.containsMouse ? "#A78BFA" : "#4B5563")
                        border.width: 1.5

                        Text {
                            anchors.centerIn: parent
                            text: "✓"
                            color: "#FFFFFF"
                            font.pixelSize: 13
                            font.bold: true
                            visible: taskItemRect.isDone
                        }

                        MouseArea {
                            id: checkArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                if (typeof wsHomePage !== "undefined" && taskItemRect.taskId) {
                                    wsHomePage.toggleTaskCompletion(taskItemRect.taskId, !taskItemRect.isDone)
                                }
                            }
                        }
                    }

                    // Priority Badge
                    Rectangle {
                        height: 20
                        width: prioText.implicitWidth + 12
                        radius: 4
                        color: {
                            if (taskItemRect.priorityLevel === "High") return Qt.rgba(0.94, 0.27, 0.27, 0.18)
                            if (taskItemRect.priorityLevel === "Low") return Qt.rgba(0.23, 0.51, 0.96, 0.18)
                            return Qt.rgba(0.96, 0.62, 0.04, 0.18)
                        }

                        Text {
                            id: prioText
                            anchors.centerIn: parent
                            text: taskItemRect.priorityLevel
                            font.pixelSize: 10
                            font.bold: true
                            font.family: "Inter"
                            color: {
                                if (taskItemRect.priorityLevel === "High") return "#F87171"
                                if (taskItemRect.priorityLevel === "Low") return "#60A5FA"
                                return "#FBBF24"
                            }
                        }
                    }

                    // Task Title
                    Text {
                        text: modelData.title || "Untitled Task"
                        color: taskItemRect.isDone ? "#64748B" : "#FFFFFF"
                        font.pixelSize: 13
                        font.weight: taskItemRect.isDone ? Font.Normal : Font.Medium
                        font.strikeout: taskItemRect.isDone
                        elide: Text.ElideRight
                        Layout.fillWidth: true
                        font.family: "Inter"
                    }

                    // Project Tag Pill
                    Rectangle {
                        visible: modelData.projectName !== ""
                        height: 18
                        width: taskProjText.implicitWidth + 10
                        radius: 4
                        color: Qt.rgba(0.55, 0.36, 0.96, 0.12)

                        Text {
                            id: taskProjText
                            anchors.centerIn: parent
                            text: modelData.projectName
                            font.pixelSize: 9
                            color: modelData.projectColor !== "" ? modelData.projectColor : "#A78BFA"
                            font.weight: Font.DemiBold
                        }
                    }

                    // Due Time Label
                    Text {
                        text: modelData.dueTimeFormatted || ""
                        color: "#64748B"
                        font.pixelSize: 11
                        font.family: "Inter"
                    }

                    // Delete Button on hover
                    Text {
                        text: "✕"
                        font.pixelSize: 11
                        color: "#94A3B8"
                        visible: taskMouse.containsMouse

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                if (typeof wsHomePage !== "undefined" && taskItemRect.taskId) {
                                    wsHomePage.deleteTask(taskItemRect.taskId)
                                }
                            }
                        }
                    }
                }

                MouseArea {
                    id: taskMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    z: -1
                }
            }
        }

        // --- Empty State ---
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: typeof wsHomePage !== "undefined" && wsHomePage.todayTasks.length === 0

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 12

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "🎉"
                    font.pixelSize: 32
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "All caught up for today!"
                    color: "#FFFFFF"
                    font.pixelSize: 14
                    font.bold: true
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "No tasks due today. Plan ahead or take a break."
                    color: "#94A3B8"
                    font.pixelSize: 12
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    width: 120
                    height: 32
                    radius: 6
                    color: Qt.rgba(1, 1, 1, 0.08)
                    border.color: Qt.rgba(1, 1, 1, 0.15)
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "+ Add Task"
                        color: "#E2E8F0"
                        font.bold: true
                        font.pixelSize: 12
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            if (typeof wsHomePage !== "undefined") {
                                wsHomePage.createNewTask("Untitled Task")
                            }
                        }
                    }
                }
            }
        }
    }
}
