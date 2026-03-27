import QtQuick 2.15
import QtQuick.Controls

Rectangle
{
    id: myRectangle

    property bool someButtonChecked: fourButtons.someButtonChecked
    property var unicueButtonsConfig: []
    property string textLabel

    signal leftClicked()
    signal rightClicked()
    signal checkedText(string text)

    Text {
        id: label
        text: textLabel
        color: "white"
        anchors {
            horizontalCenter: myRectangle.horizontalCenter
            top: myRectangle.top
        }
        font
        {
            bold: true
            pointSize: 1 + Math.min(myRectangle.height, myRectangle.width) / 7.5
        }
    }

    FourButtons
    {
        id: fourButtons

        anchors
        {
            horizontalCenter: myRectangle.horizontalCenter
            top: label.bottom
            topMargin: 5
            bottom: myRectangle.bottom
            left: myRectangle.left
            leftMargin: myRectangle.width * 0.10
        }

        buttonsConfig: unicueButtonsConfig
        onShowCheckedButtonText: (buttonText) => {
            myRectangle.checkedText(buttonText)
        }
    }

    LeftButton
    {
        id: leftButton

        anchors
        {
            left: myRectangle.left
            bottom: myRectangle.bottom

            right: fourButtons.left
            top: fourButtons.top

            margins: 5
        }

        onLeftClicked:
        {
            myRectangle.leftClicked()
        }
    }

    RightButton
    {
        id: rightButton

        anchors
        {
            left: fourButtons.right
            bottom: myRectangle.bottom

            right: myRectangle.right
            top: fourButtons.top

            margins: 5
        }

        onRightClicked:
        {
            myRectangle.rightClicked()
        }
    }
}
