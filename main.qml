import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import objects 1.0

ApplicationWindow{
    id:root
    visible: true
    minimumHeight: 480
    minimumWidth: 320
    header: Text {
        id: headerText
        text: "Верхняя часть";
        font.pixelSize: 25
    }

    Loader{
        id: mainField
        focus: true
        property string currState: "menu"
        anchors.fill: parent
        Component.onCompleted: {
            setSource("MyMenu.qml");
            item.buttonClicked.connect(startGame);
        }
    }

    function startGame(interval, minVal, maxVal, addElemCount,rowCount,maxElemCount){
        footerText.visible = false;
        headerText.visible = false;
        mainField.setSource("Game.qml",
                            {
                                "width": root.width,
                                "height": root.height,
                                "minAddValue": minVal,
                                "maxAddValue": maxVal,
                                "AddCellCount": addElemCount,
                                "interval": interval,
                                "rowCount": rowCount,
                                "maxCellCount" :maxElemCount
                            });
    }

    footer: Text{
        id:footerText
        text: "нижняя часть"
        font.pixelSize: 25
    }
}
