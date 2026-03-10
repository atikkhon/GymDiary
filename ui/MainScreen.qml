import QtQuick 2.15
import QtQuick.Controls

Item {

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
        firstButtonText: repsModel.visibleItems[0]
        secondButtonText: repsModel.visibleItems[1]
        thirdButtonText: repsModel.visibleItems[2]
        fourthButtonText: repsModel.visibleItems[3]
        onCheckedText: (reps_) => {
            reps = reps_
            tableModel.setExerciseType(typeOfExercsise, weight, reps)
            console.log(`${typeOfExercsise}, ${weight}, ${reps}`)
        }
    }
}
