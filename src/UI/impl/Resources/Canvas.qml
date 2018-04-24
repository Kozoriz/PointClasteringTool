import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtDataVisualization 1.2
import "."

Rectangle {
    id: mainView
    anchors.fill: parent

    DataPoint {
        id: graphData
    }


    Item {
        id: dataView
        anchors.fill: parent

        Scatter3D {
            id: scatterGraph
            width: dataView.width
            height: dataView.height
            shadowQuality: AbstractGraph3D.ShadowQualityNone

            Scatter3DSeries {
                id: scatterSeriesOne
                mesh: Abstract3DSeries.MeshPoint


                ItemModelScatterDataProxy {
                    itemModel: graphData.modelPoint
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
            }
        }

        MouseArea {
            id: inputArea
            anchors.fill: parent
            hoverEnabled: true
            property int mouseX: 0
            property int mouseY: 0
            property int presedX: 0
            property int presedY: 0

            onPositionChanged: {
                mouseX = mouse.x;
                mouseY = mouse.y;
            }

            onWheel: {
                var zoomLevel = scatterGraph.scene.activeCamera.zoomLevel
                if (zoomLevel > 100)
                    zoomLevel += wheel.angleDelta.y / 12.0;
                else if (zoomLevel > 50)
                    zoomLevel += wheel.angleDelta.y / 60.0;
                else
                    zoomLevel += wheel.angleDelta.y / 120.0;
                if (zoomLevel > 500)
                    zoomLevel = 500;
                else if (zoomLevel < 10)
                    zoomLevel = 10;

                scatterGraph.scene.activeCamera.zoomLevel = zoomLevel;
            }

            onClicked: {
                if (mouse.buttons && Qt.LeftButton)
                {
                    presedX = mouse.x;
                    presedY = mouse.y;
                };
            }

            onPressedChanged: {
                if (mouse.buttons && Qt.LeftButton)
                {
                    scatterGraph.scene.activeCamera.xRotation = (presedX + mouseX);
                    scatterGraph.scene.activeCamera.yRotation = (presedY + mouseY);
                }
            }

        }

        Timer {
            id: reselectTimer
            interval: 10
            running: true
            repeat: true
            onTriggered: {
                scatterGraph.scene.selectionQueryPosition = Qt.point(inputArea.mouseX, inputArea.mouseY);
            }
        }

    }
}

