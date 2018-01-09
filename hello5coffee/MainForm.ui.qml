import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    width: 640
    height: 480

    RowLayout {
        id: mainRowLayout
        x: 0
        y: 0
        width: 640
        height: 480
    }

    TabView {
        id: tabView1
        x: 0
        y: 0
        width: parent.width*2/5
        height: parent.height

        Tab {
            id: tab1
            title: "Tab"
            source: "Tab.qml"
        }

        Tab {
            id: tab21
            title: "Tab2"
            source: "Tab2.qml"
        }
    }
}
