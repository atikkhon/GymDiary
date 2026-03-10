import QtQuick 2.15

Rectangle
{
    id: rightButton
    color: "black"
    anchors
    {
        left: buttons.right
        leftMargin: 5
        top: parent.top
        topMargin: 5
        bottom: parent.bottom
        bottomMargin: 5
        right: parent.right
        rightMargin: 5
    }

    MouseArea {
        id: leftMouseArea
        anchors.fill: parent

        onClicked: {
            console.log("Вправо")
            repsModel.next()
        }
    }

    Text {
        text: qsTr(">")
        color: "white"
        anchors
        {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }
}
