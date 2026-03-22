import QtQuick 2.15
import QtQuick.Controls
import "Files"

Item {

    property int marge_value: 10
    property double height_koeff: 0.11

    property string typeOfExercsise
    property string weight
    property string reps


    Rectangle
    {
        id: myRectangle
        color: "transparent"
        anchors
        {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: one.top
            margins: 40
        }
        Component
        {
            id: forDelegate
            Item
            {
                id: myItem
                required property int index
                required property string date
                required property string exercise
                required property string lastset
                width: myRectangle.width
                height: 40
                MouseArea { anchors.fill: parent; onClicked: mySetsLog.currentIndex = myItem.index }
                Text
                {
                    anchors
                    {
                        centerIn: parent
                    }
                    font.pixelSize: 18
                    color: "white"
                    text: myItem.date + " " + myItem.exercise + " " + myItem.lastset
                }
            }
        }
        ListView
        {
            id: mySetsLog
            model: setsLogModel
            delegate: forDelegate
            verticalLayoutDirection:  ListView.BottomToTop
            height: 200
            highlight: Rectangle { color: "#4C0099"; radius: 10 }
            highlightFollowsCurrentItem: true
            width: parent.width
            anchors.bottom: parent.bottom
            clip: true
        }
    }

    LabelAndOptions {
        id: one
        buttonCheckable: true

        thisHeight: parent.height * height_koeff

        topAnchors: parent.top
        topMarginAnchors: parent.height / 2

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

        onLeftClicked: console.log("nothing")
        onRightClicked: console.log("nothing")

        onCheckedText: TypeOfExercsise_ => {
                           typeOfExercsise = TypeOfExercsise_
                       }
    }

    LabelAndOptions {
        id: two
        buttonCheckable: true

        thisHeight: parent.height * height_koeff

        topAnchors: one.bottom
        topMarginAnchors: 10

        buttonDisplayType: "TextOnly"
        textLabel: "Доп. вес"
        firstButtonText: repsModel.weightsVisibleItems[0]
        secondButtonText: repsModel.weightsVisibleItems[1]
        thirdButtonText: repsModel.weightsVisibleItems[2]
        fourthButtonText: repsModel.weightsVisibleItems[3]
        onLeftClicked: repsModel.weights_prev()
        onRightClicked: repsModel.weights_next()

        onCheckedText: weight_ => {
                           weight = weight_
                       }
    }

    LabelAndOptions {
        id: three
        clickEnable: true

        thisHeight: parent.height * height_koeff

        topAnchors: two.bottom
        topMarginAnchors: 10

        buttonDisplayType: "TextOnly"
        textLabel: "Повторы"
        firstButtonText: repsModel.repsVisibleItems[0]
        secondButtonText: repsModel.repsVisibleItems[1]
        thirdButtonText: repsModel.repsVisibleItems[2]
        fourthButtonText: repsModel.repsVisibleItems[3]
        onLeftClicked: repsModel.reps_prev()
        onRightClicked: repsModel.reps_next()

        onCheckedText: reps_ =>
        {
        reps = reps_
        db.addSet(typeOfExercsise, weight, reps)
        }
    }
}
