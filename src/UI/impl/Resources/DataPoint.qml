import QtQuick 2.1

Item {
    property alias modelPoint: dataPoint

    ListModel {
        id: dataPoint
        ListElement{ xPos: -7.91649; yPos: 3.46826; zPos: -2.78126 }
        ListElement{ xPos: -7.49495; yPos: 3.12306; zPos: -3.14539 }
        ListElement{ xPos: -7.5445; yPos: 2.85744; zPos: -3.68421 }
        ListElement{ xPos: -7.91649; yPos: 3.46826; zPos: -2.78126 }
    }
}
