import QtQuick 2.15

Rectangle
{
    signal leftClicked()

    id: leftButton
    color: "black"
    anchors
    {
        left: parent.left
        leftMargin: 5
        top: parent.top
        topMargin: 5
        bottom: parent.bottom
        bottomMargin: 5
        right: buttons.left
        rightMargin: 5
    }

    MouseArea {
        id: leftMouseArea
        anchors.fill: parent

        onClicked: {
            parent.leftClicked()
        }
    }
    Text {
        text: qsTr("<")
        color: "white"
        anchors
        {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }
}
