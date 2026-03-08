import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

RowLayout
{
    property alias firstButtonIconSource: firstButton.icon.source
    property alias firstButtonText: firstButton.text

    property alias secondButtonIconSource: secondButton.icon.source
    property alias secondButtonText: secondButton.text

    property alias thirdButtonIconSource: thirdButton.icon.source
    property alias thirdButtonText: thirdButton.text

    property alias fourthButtonIconSource: fourthButton.icon.source
    property alias fourthButtonText: fourthButton.text

    property bool buttonCheckable: false
    property bool clickEnable: false
    property string buttonDisplayType: buttonDisplayType

    signal checkedText(string text)


    id: buttonsRow
    spacing: 5
    anchors
    {
        centerIn: parent.Center
        fill: parent
        leftMargin: parent.width * 0.10
        rightMargin: parent.width * 0.10
    }

    ButtonGroup {
        id: myGroup
        exclusive: true
    }

    Button
    {
        id: firstButton
        ButtonGroup.group: myGroup
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
        icon.height: parent.height * 0.85
        icon.color: "black"
        display: buttonDisplayType
        checkable: buttonCheckable
        onClicked: {
            if(clickEnable)
            {
                checkedText(text)
            }
        }

        onToggled: {
            if (checked) {
                checkedText(text)
            }
        }

        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
    }
    Button
    {
        id: secondButton
        ButtonGroup.group: myGroup
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
        icon.height: parent.height * 0.85
        icon.color: "black"
        display: buttonDisplayType
        checkable: buttonCheckable
        onClicked: {
            if(clickEnable)
            {
                checkedText(text)
            }
        }

        onToggled: {
            if (checked) {
                checkedText(text)
            }
        }

        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
    }
    Button
    {
        id: thirdButton
        ButtonGroup.group: myGroup
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
        display: buttonDisplayType
        checkable: buttonCheckable
        icon.height: parent.height * 0.85
        icon.color: "black"
        onClicked: {
            if(clickEnable)
            {
                checkedText(text)
            }
        }

        onToggled: {
            if (checked) {
                checkedText(text)
            }
        }

        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
    }
    Button
    {
        id: fourthButton
        ButtonGroup.group: myGroup
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
        icon.height: parent.height * 0.85
        icon.color: "black"
        display: buttonDisplayType
        checkable: buttonCheckable
        onClicked: {
            if(clickEnable)
            {
                checkedText(text)
            }
        }

        onToggled: {
            if (checked) {
                checkedText(text)
            }
        }

        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
    }
}
