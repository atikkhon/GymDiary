import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls
import QtQuick.Layouts
import TableModel
import RepsModel
import "ui"

Window {
    width: 366
    height: 814
    visible: true
    title: qsTr("Hello World")

    TableModel
    {
        id: tableModel
    }
    RepsModel
    {
        id: repsModel
    }

    SwipeView
    {
        id: mySwipeView
        anchors.fill: parent
        currentIndex: 0

        orientation: Qt.Horizontal

        MainScreen { }
        TableViewScreen { }
    }

    PageIndicator
    {
        id: indicator
        count: mySwipeView.count
        currentIndex: mySwipeView.currentIndex
        anchors.bottom: mySwipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
