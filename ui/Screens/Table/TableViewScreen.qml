import QtQuick 2.15
import QtQuick.Controls

Item {
    Rectangle
    {
        id: tablemodelframe
        anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: 30

        ListView
        {
            id: myListView
            model: diaryModel
            anchors
            {
                fill: parent
                margins: 20
            }

            section.property: "date"
            section.criteria: ViewSection.FullString
            section.delegate: Text { text: section }
            delegate: Column
            {
                leftPadding: 20
                Text { text: exercise }
                Flow
                {
                    width: myListView.width
                    leftPadding: 20
                    Repeater {
                        model: sets                        // роль sets (QStringList)
                        delegate: Text { text: modelData + " " }// modelData = строка подхода
                    }
                }
            }

        }
    }
}

