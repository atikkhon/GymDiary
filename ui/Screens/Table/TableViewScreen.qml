import QtQuick 2.15
import QtQuick.Controls

Item {
    Connections
    {
        target: tableModel
        function onGetTableChanged() {
            //myRepeater.model = tableModel.getTable()
        }
    }

    // Rectangle
    // {
    //     id: tablemodelframe
    //     anchors.fill: parent

    //     TableView
    //     {
    //         id: mytableview
    //         anchors.fill: parent
    //         model: tableModel
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         columnSpacing: 1
    //         rowSpacing: 1
    //         clip: true

    //         delegate: Rectangle
    //         {
    //             implicitHeight: 40
    //             implicitWidth: 90
    //             border.color: "black"
    //             Text {
    //                 anchors.centerIn: parent
    //                 font.pixelSize: 13
    //                 text: tabledata
    //             }
    //         }
    //     }
    // }
}

