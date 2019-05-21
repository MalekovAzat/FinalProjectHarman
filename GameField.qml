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

    //новый
    signal clicked(var index);

    GridView{
        id: view
        anchors.fill:parent
        width: parent.width
        height: parent.height
        cellHeight: root.height / rowCount
        cellWidth: root.width / rowCount
        model: gameManager.cellList
        delegate: DisappearNumber{
            id:viewDelegate
            value: model.value
            number: index
            isSelected: model.isSelected
            isVisible: model.isVisible
            width: view.cellWidth
            height: view.cellHeight
            onClicked: {
                root.clicked(index);
            }
        }
    }
}
