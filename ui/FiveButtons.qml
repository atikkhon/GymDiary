import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

RowLayout
{
    property alias firstButtonSource: firstImg.source
    property alias firstButtonText: firstButton.text

    property alias secondButtonSource: secondImg.source
    property alias secondButtonText: secondButton.text

    property alias thirdButtonSource: thirdImg.source
    property alias thirdButtonText: thirdButton.text

    property alias fourthButtonSource: fourthImg.source
    property alias fourthButtonText: fourthButton.text

    property bool buttonCheckable: false
    property bool clickEnable: false


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
        checkable: buttonCheckable
        onClicked: {if(clickEnable){console.log(`Ты сделал ${text} повторений`)}}
        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
        Image {
            id: firstImg
            anchors.centerIn: parent
            height: parent.height * 0.85
            fillMode: Image.PreserveAspectFit
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
        checkable: buttonCheckable
        onClicked: {if(clickEnable){console.log(`Ты сделал ${text} повторений`)}}
        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
        Image {
            id: secondImg
            anchors.centerIn: parent
            height: parent.height * 0.85
            fillMode: Image.PreserveAspectFit
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
        checkable: buttonCheckable
        onClicked: {if(clickEnable){console.log(`Ты сделал ${text} повторений`)}}
        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
        Image {
            id: thirdImg
            anchors.centerIn: parent
            height: parent.height * 0.85
            fillMode: Image.PreserveAspectFit
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
        checkable: buttonCheckable
        onClicked: {if(clickEnable){console.log(`Ты сделал ${text} повторений`)}}
        Rectangle
        {
            anchors.fill: parent
            color: "transparent" // Прозрачный фон
            border.width: 3
            border.color: {parent.checked ? "green" : "transparent"}
        }
        Image {
            id: fourthImg
            anchors.centerIn: parent
            height: parent.height * 0.85
            fillMode: Image.PreserveAspectFit
        }
    }
}
