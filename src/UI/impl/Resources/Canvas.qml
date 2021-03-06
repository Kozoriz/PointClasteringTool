import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtDataVisualization 1.2
import "."

Rectangle {
    id: mainView
    anchors.fill: parent

    function addPoint(x, y, z){
        graphData.modelPoint.append({"xPos": x,"yPos": y,"zPos": z})

    }

    function clear() {
        graphData.modelPoint.clear()
    }

    DataPoint {
        id: graphData
    }

    Item {
        id: dataView
        anchors.fill: parent

        // LOW PERFORMANCE WITH 1kk+ dots
        Scatter3D { // TODO use : pcl or https://github.com/MASKOR/Qt3DPointcloudRenderer
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
            Component.onCompleted:
            {
//                for (var i=0; i< Wrapper.Cloude.length; i++)
//                   graphData.modelPoint.append({"xPos": RedebleOject.Cloude[i].x,"yPos": RedebleOject.Cloude[i].y,"zPos": RedebleOject.Cloude[i].z})
            }

            onClicked: {
                if (mouse.buttons)
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
    }
}

