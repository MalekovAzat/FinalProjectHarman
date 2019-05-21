import QtQuick 2.0

Item {
    id:root
    visible: true
    width: maxWidth
    height: 30

    property alias currState: progressLine.state

    property int timerInterval:10
    property int maxWidth
    property int minWidth


    signal timerTriggered

    Rectangle{
        id: container
        width: maxWidth + 10
        height: 30
        color: "black"

        Rectangle{
            id: progressLine
            height: 5
            visible: true
            anchors.centerIn: parent
            radius: 15

            states:[
                State {
                    name: "zeroWidth"
                    PropertyChanges {
                        target: progressLine
                        color: Qt.rgba(79/255,239/255,55/255);
                        width: minWidth
                    }
                },
                State {
                    name: "fullWidth"
                    PropertyChanges {
                        target: progressLine
                        color: Qt.rgba(217/255, 27/255, 27/255);
                        width: maxWidth - 20
                    }
                }
            ]
            transitions: [
                Transition {
                    from: "zeroWidth"
                    to: "fullWidth"
                    PropertyAnimation{
                        target: progressLine
                        properties:  "width,color"
                        duration: timerInterval*1000
                        easing.type: Easing.Linear
                    }
                }
            ]
        }
    }

    Timer{
        id: timer
        interval: timerInterval*1000
        onTriggered: {
            currState = "zeroWidth";
            timer.start();
            timerTriggered();
            currState = "fullWidth";
        }
    }


    function start(){
        timer.start();
        currState = "fullWidth";
    }

    function stop(){
        timer.stop();
        currState = "zeroWidth";
    }

    function restart(){
        currState = "zeroWidth";
        timer.restart();
        root.start()
    }
}
