import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

import data_meneger 1.0

Window {
    title: qsTr("untitled")
    width: 1280
    height: 768
    visible: true

    DataMeneger{
        id: dataMeneger
    }

    GroupBox {
        id: groupBox
        anchors.fill: parent
        anchors.bottomMargin: 22
        anchors.leftMargin: 17
        anchors.topMargin: 217
        anchors.rightMargin: 428
        title: qsTr("3D Model")


        Loader {
            id:loader
            anchors.fill: parent
            source: "Canvas.qml"
        }

    }

}