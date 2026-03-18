import QtQuick 2.15
import QtQuick.Controls

Item {
    Rectangle
    {
        id: tablemodelframe
        anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: 50
        color: "#000033"

        Button
        {
            id: recreateJsonButton
            text: "Очистить дневник"
            anchors
            {
                horizontalCenter: parent.horizontalCenter
                bottom: myListView.top
                bottomMargin: 15
            }
            onClicked: diaryModel.recreateJson()
        }
        ListView
        {
            id: myListView
            model: diaryModel
            anchors
            {
                fill: parent
                margins: 30
            }

            section.property: "date"
            section.criteria: ViewSection.FullString
            section.delegate: Text
            {
                color: "white"
                font.bold: true
                font.pixelSize: 18
                text: section
            }
            delegate: Column
            {
                leftPadding: 20
                Text
                {
                    color: "white"
                    font.pixelSize: 18
                    text: exercise
                }
                Flow
                {
                    width: myListView.width
                    leftPadding: 20
                    Repeater {
                        model: sets                        // роль sets (QStringList)
                        delegate: Text
                        {
                            color: "white"
                            font.pixelSize: 18
                            text: modelData + " "
                        }// modelData = строка подхода
                    }
                }
            }

        }
    }
}

