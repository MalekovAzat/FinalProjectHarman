import QtQuick 2.0

Rectangle{
    id:root
//    width: 50
//    height: 50
    visible: true
    property bool isVisible : false
    property bool isSelected: false

    property int value // значение для ячейки
    property var rectColor: Qt.rgba(Math.random(),Math.random(),Math.random(),1);
    property int defaultTextSize: 25
    property int number:0

    property alias textSize :currentValueText.font.pixelSize
    property alias textColor : currentValueText.color

    signal clicked(var index)

    Text {
        id: currentValueText
        anchors.centerIn: parent
        text: + parent.value
        font.pixelSize: defaultTextSize
        visible: isVisible
    }

    MouseArea{
        id:mouseArea
        anchors.fill: root
        onClicked: {
            root.clicked(root.number)
        }
    }

    states: [
        State {
            name: "Selected"
            PropertyChanges {
                target: root
                color: "black"
                textColor: "white"
                textSize: defaultTextSize + 10
                radius: 50
                opacity: 1
            }
        },
        State {
            name: "unSelected"
            PropertyChanges {
                target: root
                color: rectColor
                textSize: defaultTextSize
                opacity: 1
                radius: 10
            }
        },
        State {
            name: "unVisible"
            PropertyChanges {
                target: root
                radius: 10
                opacity: 0
            }
        }
    ]

    state: {
        if(isVisible){
            return isSelected ? "Selected": "unSelected";
        }
        return "unVisible";
    }

    transitions:[
        Transition {
            from: "Selected"
            to: "unSelected"
            NumberAnimation {
                target: root
                properties: "textSize,radius"
                duration: 400
                easing.type:Easing.InBack
            }
            ColorAnimation {
                duration: 400
            }
        },
        Transition {
            from: "unSelected"
            to: "Selected"
            NumberAnimation {
                target: root
                properties: "textSize,radius"
                duration: 400
                easing.type:Easing.InBack
            }
            ColorAnimation {
                duration: 400
            }
        },
        Transition {
            from: "Selected"
            to: "unVisible"

            NumberAnimation {
                target: root
                properties: "opacity"
                duration: 400
                easing.type: Easing.InBack
            }
        },
        Transition {
            from: "unVisible"
            to: "unSelected"

            NumberAnimation {
                target: root
                properties: "opacity"
                duration: 600
                easing.type: Easing.InExpo
            }
        }
    ]

    function changeState(){
        isSelected = isSelected ? false : true;
    }

    function setToVisible(){
        root.isSelected = false;
        root.isVisible = true;
    }

    function setToInvisible(){
        root.isSelected = false;
        root.isVisible = false;
    }
}
