import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

RowLayout
{
    id: myRowLayout

    property var buttonsConfig: []
    property bool someButtonChecked: myButtonGroup.checkedButton

    signal showCheckedButtonText(string text)

    spacing: 5

    ButtonGroup {
        id: myButtonGroup
        exclusive: true
    }

    Repeater
    {
        model: myRowLayout.buttonsConfig

        delegate: MyButton {
            ButtonGroup.group: myButtonGroup

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 5
            Layout.bottomMargin: 5

            myButtonIconSource: modelData.iconSource
            myButtonButtonText: modelData.text
            myButtonDisplayType: modelData.displayType
            myButtonCheckable: modelData.checkable
            myButtonClickEnable: modelData.clickEnable

            onShowMyButtonCheckedText: function(buttonText) {
                myRowLayout.showCheckedButtonText(buttonText)
            }
        }
    }
}
