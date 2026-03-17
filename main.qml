import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls
import QtQuick.Layouts
import TableModel
import RepsModel
import "ui/Screens/Main"
import "ui/Screens/Table"

Window {
    width: 366
    height: 814
    visible: true
    title: qsTr("Gym Diary")

    TableModel
    {
        id: tableModel
    }
    RepsModel
    {
        id: repsModel
        onRepsVisibleItemsChanged:
        {
            console.log(`reps изменилось и вернуло: ${repsVisibleItems}`)
        }
        onWeightsVisibleItemsChanged:
        {
            console.log(`weights изменилось и вернуло ${weightsVisibleItems}`)
        }
        Component.onCompleted: {
            console.log("Начальное repsVisibleItems =", repsVisibleItems)
            console.log("Начальное weightsVisibleItems =", weightsVisibleItems)
        }
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
}
