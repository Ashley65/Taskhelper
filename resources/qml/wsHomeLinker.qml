import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "wsHomePage" as WsHome

Rectangle {
    id: root
    anchors.fill: parent
    color: "#14151F"

    readonly property bool isStacked: root.width < 700

    Flickable {
        id: scrollArea
        anchors.fill: parent
        contentWidth: width
        contentHeight: contentCol.implicitHeight + 48
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        Item {
            width: scrollArea.width
            height: Math.max(scrollArea.height, contentCol.implicitHeight + 48)

            ColumnLayout {
                id: contentCol
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: root.width < 640 ? 16 : 24
                spacing: 18

                WsHome.HeaderSection {
                    Layout.fillWidth: true
                }

                GridLayout {
                    id: columnsLayout
                    Layout.fillWidth: true
                    columns: root.isStacked ? 1 : 2
                    rowSpacing: 16
                    columnSpacing: 16

                    WsHome.RecentNotesColumn {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.isStacked ? 340 : 440
                        Layout.minimumHeight: 280
                    }

                    WsHome.TaskFocusColumn {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.isStacked ? 340 : 440
                        Layout.minimumHeight: 280
                    }
                }
            }
        }
    }
}
