import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import objects 1.0

Rectangle {
    id:root
    visible: true
    color: "blue"
    property int rowCount;
    property alias model: view.model
    signal cellSelected(var pos,var val,var isSelected)

    GridView{
        id: view
        anchors.fill:parent
        width: parent.width
        height: parent.height
        cellHeight: root.height / rowCount
        cellWidth: root.width / rowCount
        model: gameManager.cellList
        delegate:  DisappearNumber{
            id:viewDelegate
            value: model.value
            number: index
            isSelected: false
            isVisible: false
            width: view.cellWidth
            height: view.cellHeight
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                var target = view.itemAt(mouseX, mouseY);
                if(target.isVisible){
                    var tN = target.number;
                    var tV = target.value;
                    var tIS = target.isSelected;
                    root.cellSelected(tN,tV,tIS);
                }
            }
        }
    }

    function changeStateForPos(number){
        var target = view.contentItem.children[number];
        target.changeState();
    }

    function hideElement(number){
        var target = view.contentItem.children[number];
        target.setToInvisible();
    }

    function showElement(number){
        var target = view.contentItem.children[number];
        target.setToVisible();
    }

}
