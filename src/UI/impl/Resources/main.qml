import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.0
import "."

ApplicationWindow {
    title: qsTr("Point Clustering Tool")
    width: 1280
    height: 768
    color: "#d9d9d9"
    visible: true

    Connections {
        target: Wrapper
        onNewPointAdded : {
//            console.log(Wrapper.newPoint.x, Wrapper.newPoint.y, Wrapper.newPoint.z)
            canvas.addPoint(Wrapper.newPoint.x, Wrapper.newPoint.y, Wrapper.newPoint.z)
//            Wrapper.newPoint
//            Canvas.some = 2
//            graphData.modelPoint.append({"xPos": RedebleOject.Cloude[i].x,"yPos": RedebleOject.Cloude[i].y,"zPos": RedebleOject.Cloude[i].z})
        }

        onCloudNameAdded : {
            cloudsListModel.append({"name":Wrapper.addedCloudName})
        }
    }


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

            Canvas {
                id : canvas
            }
        }

        ListView {
            id: cloudsList
            width: parent.width*0.2
            height: parent.height*0.5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            delegate: Item {
                width: parent.width
                height: 15
                Row {
                    id: listItemRow
                    Text {
                        id: listItemRowText
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 5
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        // TODO temp before tabs implemented
                        canvas.clear()
                        cloudsList.currentIndex = index
                        Wrapper.cloudChoosen = cloudsListModel.get(index).name
                    }
                }

            }
            model: ListModel {
                id:cloudsListModel
            }
            highlight: Rectangle {
                color: '#aaaaaa'
            }
        }
    }
    Component.onCompleted: {
//        for (var i=0; i< 100; i++)
//        {
//            cloudsListModel.append({"name":"some" +i})
//        }
    }
    menuBar: MenuBar {
            Menu {
                title: qsTr("&File")
                Action { text: qsTr("&New...") }
                Action {
                    text: qsTr("&Open...")
                    onTriggered: newCloudFileOpenDialog.open()
                }
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


    FileDialog {
        id: newCloudFileOpenDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            Wrapper.openedFile = newCloudFileOpenDialog.fileUrls[0]
            newCloudFileOpenDialog.close()
        }
        onRejected: {
            newCloudFileOpenDialog.close()
        }
        nameFilters: [ "PointCloud files (*.pointcloud)", "All files (*)" ]
    }

}

/*##^## Designer {
    D{i:40;anchors_height:100;anchors_width:100;anchors_x:822;anchors_y:89}
}
 ##^##*/
