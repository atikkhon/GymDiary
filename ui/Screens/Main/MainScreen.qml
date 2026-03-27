import QtQuick 2.15
import QtQuick.Controls
import "Files"

Item {

    property int marge_value: 10
    property double height_koeff: 0.11

    property string typeOfExercsise
    property string weight
    property string reps

    SetsLog
    {
        anchors
        {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: one.top
            margins: 40
        }
    }

    LabelAndOptions
    {
        id: one
        height: parent.height * height_koeff
        color: "#000033"
        anchors
        {
            horizontalCenter: parent.horizontalCenter
            left: parent.left
            top: parent.top
            topMargin: parent.height / 2
            leftMargin: 15
        }

        textLabel: "Выбор упражнений"

        unicueButtonsConfig: [
            { iconSource: repsModel.exercisesVisibleItems[0], text: repsModel.exercisesVisibleNames[0], displayType: AbstractButton.IconOnly, checkable: true, clickEnable: false },
            { iconSource: repsModel.exercisesVisibleItems[1], text: repsModel.exercisesVisibleNames[1], displayType: AbstractButton.IconOnly, checkable: true, clickEnable: false },
            { iconSource: repsModel.exercisesVisibleItems[2], text: repsModel.exercisesVisibleNames[2], displayType: AbstractButton.IconOnly, checkable: true, clickEnable: false },
            { iconSource: repsModel.exercisesVisibleItems[3], text: repsModel.exercisesVisibleNames[3], displayType: AbstractButton.IconOnly, checkable: true, clickEnable: false }
        ]

        onLeftClicked: repsModel.exercises_prev()
        onRightClicked: repsModel.exercises_next()

        onCheckedText: TypeOfExercsise_ => {
            typeOfExercsise = TypeOfExercsise_
        }
    }

    LabelAndOptions
    {
        id: two
        height: parent.height * height_koeff
        color: "#000033"
        anchors
        {
            horizontalCenter: parent.horizontalCenter
            left: parent.left
            top: one.bottom
            topMargin: 10
            leftMargin: 15
        }

        textLabel: "Доп. вес"

        unicueButtonsConfig: [
            { iconSource: "", text: repsModel.weightsVisibleItems[0], displayType: AbstractButton.TextOnly, checkable: true, clickEnable: false },
            { iconSource: "", text: repsModel.weightsVisibleItems[1], displayType: AbstractButton.TextOnly, checkable: true, clickEnable: false },
            { iconSource: "", text: repsModel.weightsVisibleItems[2], displayType: AbstractButton.TextOnly, checkable: true, clickEnable: false },
            { iconSource: "", text: repsModel.weightsVisibleItems[3], displayType: AbstractButton.TextOnly, checkable: true, clickEnable: false }
        ]

        onLeftClicked: repsModel.weights_prev()
        onRightClicked: repsModel.weights_next()

        onCheckedText: weight_ => {
            weight = weight_
        }
    }

    LabelAndOptions
    {
        id: three

        height: parent.height * height_koeff
        color: "#000033"
        anchors
        {
            horizontalCenter: parent.horizontalCenter
            left: parent.left
            top: two.bottom
            topMargin: 10
            leftMargin: 15
        }

        textLabel: "Повторы"

        unicueButtonsConfig: [
            { iconSource: "", text: repsModel.repsVisibleItems[0], displayType: AbstractButton.TextOnly, checkable: false, clickEnable: true },
            { iconSource: "", text: repsModel.repsVisibleItems[1], displayType: AbstractButton.TextOnly, checkable: false, clickEnable: true },
            { iconSource: "", text: repsModel.repsVisibleItems[2], displayType: AbstractButton.TextOnly, checkable: false, clickEnable: true },
            { iconSource: "", text: repsModel.repsVisibleItems[3], displayType: AbstractButton.TextOnly, checkable: false, clickEnable: true }
        ]

        onLeftClicked: repsModel.reps_prev()
        onRightClicked: repsModel.reps_next()

        onCheckedText: reps_ =>
        {
            if (one.someButtonChecked & two.someButtonChecked)
            {
                reps = reps_
                db.addSet(typeOfExercsise, weight, reps)
            }
        }
    }
}
