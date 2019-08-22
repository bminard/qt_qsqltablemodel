// MyItem.qml
import QtQuick 2.0

Item {
    id: item
    width: 100; height: 100

    signal qmlSignal(string msg)

    MouseArea {
        anchors.fill: parent
        onClicked: item.qmlSignal("Hello from QML")
    }
}
