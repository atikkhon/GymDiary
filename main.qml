import QtQuick 2.15
import QtQuick.Window 2.15
import "ui"
import TableModel

Window {
    width: 366
    height: 814
    visible: true
    title: qsTr("Hello World")

    property int marge_value: 10
    property double height_koeff: 0.1

    property string typeOfExercsise
    property string weight
    property string reps

    LabelAndOptions
    {
        id: one
        buttonCheckable: true
        thisHeight: parent.height * height_koeff
        topAnchors: parent.top
        topMarginAnchors: marge_value
        textLabel: "Выбор упражнений"
        buttonDisplayType: "IconOnly"
        firstButtonIconSource: "qrc:/ui/pictures/pullups.png"
        firstButtonText: "Подтягивания"
        secondButtonIconSource: "qrc:/ui/pictures/paralets.png"
        secondButtonText: "Брусья"
        thirdButtonIconSource: "qrc:/ui/pictures/quads.png"
        thirdButtonText: "Присед"
        fourthButtonIconSource: "qrc:/ui/pictures/deadlift.png"
        fourthButtonText: "Становая"

        onCheckedText: (TypeOfExercsise_) =>
        {
            typeOfExercsise = TypeOfExercsise_
        }
    }

    LabelAndOptions
    {
        id: two
        buttonCheckable: true
        thisHeight: parent.height * height_koeff
        topAnchors: one.top
        topMarginAnchors: marge_value + thisHeight
        buttonDisplayType: "TextOnly"
        textLabel: "Доп. вес"
        firstButtonText: "5 кг"
        secondButtonText: "7.5 кг"
        thirdButtonText: "10 кг"
        fourthButtonText: "12.5 кг"

        onCheckedText: (weight_) =>
        {
            weight = weight_
        }
    }

    LabelAndOptions
    {
        id: three
        clickEnable: true
        thisHeight: parent.height * height_koeff
        topAnchors: two.top
        topMarginAnchors: marge_value + thisHeight
        buttonDisplayType: "TextOnly"
        textLabel: "Повторы"
        firstButtonText: "10"
        secondButtonText: "11"
        thirdButtonText: "12"
        fourthButtonText: "13"
        onCheckedText: (reps_) => {
            reps = reps_
            console.log(`${typeOfExercsise}, ${weight}, ${reps}`)
        }
    }

    Rectangle
    {
        id: tablemodelframe
        border.color: "blue"
        anchors
        {
            top: three.bottom
            topMargin: 50
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        TableView
        {
            anchors.fill: parent
            columnSpacing: 3
            rowSpacing: 3
            clip: true

            model: TableModel {}

            delegate: Rectangle
            {
                implicitHeight: 40
                implicitWidth: 90
                border.color: "red"
                Text {
                    text: tabledata
                    anchors.centerIn: parent
                }
            }
        }
    }

}
