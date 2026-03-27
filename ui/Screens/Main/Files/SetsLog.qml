import QtQuick 2.15

Rectangle
{
    id: myRectangle
    color: "transparent"

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
            required property int setid
            width: myRectangle.width
            height: 40
            MouseArea
            {
                anchors.fill: parent
                onClicked: mySetsLog.currentIndex = myItem.index
                onDoubleClicked: db.removeSetFromJson(myItem.setid)
            }
            Text
            {
                anchors
                {
                    centerIn: parent
                }
                font.pixelSize: 17
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
