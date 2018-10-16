import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4
import Qt.labs.folderlistmodel 2.2

ApplicationWindow {
    title: qsTr("Point Clustering Tool")
    width: 1280
    height: 768
    color: "#d9d9d9"
    visible: true

    SplitView {
        id: splitView
        anchors.fill: parent

        Rectangle {
            id: groupBox
            width: parent.width*0.8
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.top: parent.top

            Loader {
                id:loader
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                source: "Canvas.qml"
            }

        }
        ListView
        {
            id: dirTreeView
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top

            FolderListModel
            {
                id: dirModel
                folder: "/home/andrii/workspace/git/PointClasteringTool/" // TODO set from model
                nameFilters: ["*.*"]
            }
            Component {
                id: fileDelegate
                Text { text: fileName }
            }

            model: dirModel
            delegate: fileDelegate
        }
    }
    menuBar: MenuBar {
            Menu {
                title: qsTr("&File")
                Action { text: qsTr("&New...") }
                Action { text: qsTr("&Open...") }
                Action { text: qsTr("&Save") }
                Action { text: qsTr("Save &As...") }
                MenuSeparator { }
                Action { text: qsTr("&Quit") }
            }
            Menu {
                title: qsTr("&Edit")
                Action { text: qsTr("Cu&t") }
                Action { text: qsTr("&Copy") }
                Action { text: qsTr("&Paste") }
            }
            Menu {
                title: qsTr("&Help")
                Action { text: qsTr("&About") }
            }
        }

}

/*##^## Designer {
    D{i:40;anchors_height:100;anchors_width:100;anchors_x:822;anchors_y:89}
}
 ##^##*/
