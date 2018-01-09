import QtQuick 2.6
import QtQuick.Controls 2.0

Component {
    Page {
        id:appsettingPages

        SwipeView {
            id: swipeview
            currentIndex: 0
            anchors.fill: parent

            AdminConfigPage {
                id: configPage
                width: swipeview.width
                height: swipeview.height
            }
        }

        header: TabBar {
            id: tabBar
            currentIndex: swipeview.currentIndex

            TabButton {
                text: "Cài đặt chung"
                onClicked: {
                    swipeview.currentIndex = 0
                }
            }
        }
    }
}
