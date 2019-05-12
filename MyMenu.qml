import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle{
    id: root
    width: 500
    height: 500
    color: "red"
    property int itemAngle: 60
    property int itemSize: 200
    signal buttonClicked(var interval ,var minVal,
                         var maxVal,var addElemCount,
                         var rowCount,var maxElemCount)

    //добавить рекордные значения

    ListModel{
        id: dataModel
        ListElement{
            name: "Легкий"
            minValue: 1
            maxValue: 7
            addElemCount: 3
            interval: 10
            size: "5X5"
            color: "green"
            rowCount: 5
            maxElemCount: 25
        }
        ListElement{
            name: "Нормальный"
            minValue: 1
            maxValue: 10
            addElemCount: 5
            interval: 6
            size: "5X5"
            color: "red"
            rowCount: 5
            maxElemCount: 25
        }
        ListElement{
            name: "Трудный"
            minValue: 1
            maxValue: 12
            addElemCount: 5
            interval:5
            size: "5X5"
            rowCount: 5
            maxElemCount: 25
            //                color: Qt.rgba(255/255, 255/255,0,1);
        }
        ListElement{
            name: "Невыносимый"
            minValue: 1
            maxValue: 15
            addElemCount: 4
            interval:3
            rowCount: 5
            maxElemCount: 25
            //                color: Qt.rgba(255/255, 153/255, 0, 1);
        }
        ListElement{
            name: "Безумный"
            minValue: 1
            maxValue: 20
            addElemCount: 4
            interval:5
            size: "5X5"
            rowCount: 5
            maxElemCount: 25
            //                color: Qt.rgba(255/255,0,0,1);
        }
    }

    PathView {
        id: view
        visible: parent.visible
        currentIndex: 3
        anchors.fill: parent
        model: dataModel
        pathItemCount: 4
        focus: true
        Keys.onLeftPressed: decrementCurrentIndex()
        Keys.onRightPressed: incrementCurrentIndex()
        path: Path {
            startX: 0
            startY: height / 2

            PathPercent { value: 0.0 }
            PathAttribute { name: "z"; value: 0 }
            PathAttribute { name: "angle"; value: itemAngle }
            PathAttribute { name: "origin"; value: 0 }
            PathLine {
                x: (view.width - itemSize) / 2
                y: view.height / 2
            }

            PathAttribute { name: "angle"; value: itemAngle }
            PathAttribute { name: "origin"; value: 0 }
            PathPercent { value: 0.49 }
            PathAttribute { name: "z"; value: 10 }
            PathLine { relativeX: 0; relativeY: 0 }

            PathAttribute { name: "angle"; value: 0 }
            PathLine {
                x: (view.width - itemSize) / 2 + itemSize
                y: view.height / 2
            }

            PathAttribute { name: "angle"; value: 0 }
            PathPercent { value: 0.51 }
            PathLine { relativeX: 0; relativeY: 0 }

            PathAttribute { name: "z"; value: 10 }
            PathAttribute { name: "angle"; value: -itemAngle }
            PathAttribute { name: "origin"; value: itemSize }
            PathLine {
                x: view.width
                y: view.height / 2
            }
            PathPercent { value: 1 }
            PathAttribute { name: "z"; value: 0 }
            PathAttribute { name: "angle"; value: -itemAngle }
            PathAttribute { name: "origin"; value: itemSize }
        }

        delegate: Rectangle {
            id:delegate
            visible: parent.visible
            property real rotationAngle: PathView.angle
            property real rotationOrigin: PathView.origin

            width: itemSize
            height: width
            z: PathView.z
            color: model.color
            radius: 5

            transform: Rotation {
                axis { x: 0; y: 1; z: 0 }
                angle: rotationAngle
                origin.x: rotationOrigin
            }

            Text {
                anchors.top: parent.top
                anchors.horizontalCenter: delegate.horizontalCenter
                font.pointSize: 30
                text: model.name
            }

            Text{
                anchors.centerIn: parent
                font.pointSize: 25
                text: model.size
            }

            Button{
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: delegate.horizontalCenter
                text: "начать"
                onClicked: root.buttonClicked(model.interval,model.minValue,
                                              model.maxValue,model.addElemCount,
                                              model.rowCount,model.maxElemCount);
            }
        }
    }
}
