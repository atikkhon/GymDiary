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
        thisHeight: parent.height * height_koeff
        topAnchors: parent.top
        topMarginAnchors: marge_value
        textLabel: "Выбор упражнений"
        firstButtonSource: "qrc:/ui/pictures/pullups.png"
        secondButtonSource: "qrc:/ui/pictures/paralets.png"
        thirdButtonSource: "qrc:/ui/pictures/quads.png"
        fourthButtonSource: "qrc:/ui/pictures/deadlift.png"
    }

    LabelAndOptions
    {
        id: two
        thisHeight: parent.height * height_koeff
        topAnchors: one.top
        topMarginAnchors: marge_value + thisHeight
        textLabel: "Доп. вес"
    }

    LabelAndOptions
    {
        id: three
        thisHeight: parent.height * height_koeff
        topAnchors: two.top
        topMarginAnchors: marge_value + thisHeight
        textLabel: "Повторы"
    }

}
