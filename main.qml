import QtQuick 2.15
import QtQuick.Window 2.15
import "ui"

Window {
    width: 366
    height: 814
    visible: true
    title: qsTr("Hello World")

    property int marge_value: 10
    property double height_koeff: 0.1

    LabelAndOptions
    {
        id: one
        buttonCheckable: true
        clickEnable: false
        thisHeight: parent.height * height_koeff
        topAnchors: parent.top
        topMarginAnchors: marge_value
        textLabel: "Выбор упражнений"
        firstButtonSource: "qrc:/ui/pictures/pullups.png"
        firstButtonText: "Подтягивания"
        secondButtonSource: "qrc:/ui/pictures/paralets.png"
        secondButtonText: "Брусья"
        thirdButtonSource: "qrc:/ui/pictures/quads.png"
        thirdButtonText: "Присед"
        fourthButtonSource: "qrc:/ui/pictures/deadlift.png"
        fourthButtonText: "Становая"
    }

    LabelAndOptions
    {
        id: two
        buttonCheckable: true
        clickEnable: false
        thisHeight: parent.height * height_koeff
        topAnchors: one.top
        topMarginAnchors: marge_value + thisHeight
        textLabel: "Доп. вес"
        firstButtonText: "5 кг"
        secondButtonText: "7.5 кг"
        thirdButtonText: "10 кг"
        fourthButtonText: "12.5 кг"
    }

    LabelAndOptions
    {
        id: three
        buttonCheckable: false
        clickEnable: true
        thisHeight: parent.height * height_koeff
        topAnchors: two.top
        topMarginAnchors: marge_value + thisHeight
        textLabel: "Повторы"
        firstButtonText: "10"
        secondButtonText: "11"
        thirdButtonText: "12"
        fourthButtonText: "13"
    }

}
