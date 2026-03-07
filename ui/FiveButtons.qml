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

    id: buttonsRow
    spacing: 5
    anchors
    {
        centerIn: parent.Center
        fill: parent
        leftMargin: parent.width * 0.10
        rightMargin: parent.width * 0.10
    }

    Button
    {
        id: firstButton
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
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
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
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
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
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
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.topMargin: 5
        Layout.bottomMargin: 5
        Image {
            id: fourthImg
            anchors.centerIn: parent
            height: parent.height * 0.85
            fillMode: Image.PreserveAspectFit
        }
    }
}
