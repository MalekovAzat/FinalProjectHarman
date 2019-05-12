import QtQuick 2.0

Item {
    id:root
    property int currHeight:40
    property int currWidth: 40
    property int fontSize: 25
    property alias value: valueView.text

    property alias textColor: valueView.color
    property alias backgroundColor: rect.color

    Rectangle{
        id: rect
        visible: true
        width: currWidth
        height: currHeight
        Text {
            id: valueView
            anchors.centerIn: parent
            text: value.toString();
            font.pixelSize: fontSize;
        }
    }

    function changeValue(newValue){
        value = newValue.toString();
    }
}
