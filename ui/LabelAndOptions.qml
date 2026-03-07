import QtQuick 2.15

Rectangle
{

    property double thisHeight: thisHeight

    property alias buttonCheckable: buttons.buttonCheckable
    property alias clickEnable: buttons.clickEnable

    property alias topAnchors: label_and_options.anchors.top
    property alias topMarginAnchors: label_and_options.anchors.topMargin
    property alias textLabel: label.text

    property alias firstButtonSource: buttons.firstButtonSource
    property alias firstButtonText: buttons.firstButtonText

    property alias secondButtonSource: buttons.secondButtonSource
    property alias secondButtonText: buttons.secondButtonText

    property alias thirdButtonSource: buttons.thirdButtonSource
    property alias thirdButtonText: buttons.thirdButtonText

    property alias fourthButtonSource: buttons.fourthButtonSource
    property alias fourthButtonText: buttons.fourthButtonText


    id: label_and_options
    height: thisHeight
    color: "white"

    anchors
    {
        horizontalCenter: parent.horizontalCenter
        left: parent.left
        leftMargin: 15
    }

    Text {
        id: label
        color: "black"
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
        }
    }

    Rectangle
    {
        id: options
        border.color: "black"
        color: "white"
        anchors
        {
            horizontalCenter: parent.horizontalCenter
            top: label.bottom
            topMargin: 5
            bottom: parent.bottom
            left: parent.left
        }

        FiveButtons
        {
            id: buttons
        }
    }
}
