import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import objects 1.0


Rectangle{
    id:root
    visible: true

    property alias minAddValue: manager.minAddVal
    property alias maxAddValue: manager.maxAddVal
    property alias addCellCount: manager.addCellCount
    property alias interval: indicator.timerInterval
    property alias rowCount: gamefield.rowCount
    property alias maxCellCount: manager.cellCount

    //сигнал о завершении игры
    signal gameEnd()

    Manager{
        id: manager
        onChangeMainValue: {
            mainNum.changeValue(newMainValue);
       }

        onEndGame: {
            indicator.stop();
            //показать результаты игры
       }

       onRestartTimer: {
           indicator.restart();
           manager.zeroingSum();
           manager.changeGeneralState();
       }
    }

    EndTimeIndicator{
       id: indicator
       currState: "zeroWidth"
       anchors.top: root.top
       minWidth: 40
       maxWidth: root.width
       onTimerTriggered: {
           manager.zeroingSum();
           manager.changeGeneralState();
       }
    }

    GameField{
       rowCount: 10
       width: root.width
       height: root.height - indicator.height
       model: manager.cellList
       id:gamefield
       anchors.bottom: root.bottom
       onClicked:{
            manager.cellClicked(index);
       }
    }

    Rectangle{
        width: 200
        height: 20
        color: "red"
        anchors.horizontalCenter: parent.horizontalCenter

        MouseArea{
            anchors.fill:parent
            onClicked: {
                indicator.start();
            }
        }
    }

    MainNumber{
        id: mainNum
        anchors.centerIn: parent
        currHeight: 30
        currWidth: 30
        fontSize: 25
        backgroundColor: "Black"
        textColor: "white"
        value: "20"
    }
}
