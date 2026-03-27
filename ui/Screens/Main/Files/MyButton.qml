import QtQuick 2.15
import QtQuick.Controls

Button
{
    id: myButton

    property string myButtonIconSource
    property string myButtonButtonText
    property int myButtonDisplayType

    property bool myButtonCheckable
    property bool myButtonClickEnable

    signal showMyButtonCheckedText(string text)

    text: myButtonButtonText
    display: myButtonDisplayType
    checkable: myButtonCheckable

    icon.source: myButtonIconSource
    icon.height: myButton.height * 0.6
    icon.width: myButton.width * 0.6
    icon.color: "white"

    font
    {
        bold: true
        pointSize: 0.1 + Math.min(myButton.height, myButton.width) / 4
    }

    //Когда менятся текст на кнопке(по нажатию < и >)
    onTextChanged:
    {
        if (myButtonDisplayType == AbstractButton.TextOnly && checked)
        showMyButtonCheckedText(text)
    }
    //Когда кликаем на кнпоки повторений
    onClicked: {
        if(myButtonClickEnable && !checked && myButtonDisplayType == AbstractButton.TextOnly)
        {
            showMyButtonCheckedText(text)
        }
    }
    // Когда кнопка меняет состояние: нажата/отжата
    onToggled: {
        showMyButtonCheckedText(text)
    }

    Rectangle
    {
        anchors.fill: myButton
        color: "transparent" // Прозрачный фон
        border.width: 3
        border.color: {myButton.checked ? "white" : "transparent"}
    }
}
