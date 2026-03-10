import QtQuick 2.15

Rectangle
{
    property double thisHeight: thisHeight

    property alias buttonCheckable: buttons.buttonCheckable
    property alias clickEnable: buttons.clickEnable
    property alias buttonDisplayType: buttons.buttonDisplayType

    property alias topAnchors: label_and_options.anchors.top
    property alias topMarginAnchors: label_and_options.anchors.topMargin
    property alias textLabel: label.text

    property alias firstButtonIconSource: buttons.firstButtonIconSource
    property alias firstButtonText: buttons.firstButtonText

    property alias secondButtonIconSource: buttons.secondButtonIconSource
    property alias secondButtonText: buttons.secondButtonText

    property alias thirdButtonIconSource: buttons.thirdButtonIconSource
    property alias thirdButtonText: buttons.thirdButtonText

    property alias fourthButtonIconSource: buttons.fourthButtonIconSource
    property alias fourthButtonText: buttons.fourthButtonText

    signal checkedText(string text)


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

        LeftButton { }
        RightButton { }

        FiveButtons
        {
            id: buttons
            onCheckedText: (buttonText) => {
                label_and_options.checkedText(buttonText)
            }
        }
    }
}
