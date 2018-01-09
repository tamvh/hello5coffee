import QtQuick 2.0
import QtQuick.Controls 1.5 as Controls
import MainController 1.0

Grid {
    id: grid1
    transformOrigin: Item.Center
    anchors.fill: parent
    columns: 2

    Row {
        id: row1
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        anchors.margins: 0
        Text {
            id:printerName
            width: 140
            anchors.left: parent.left
            anchors.top: parent.top
            text:"Tên máy in:"
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        TextEdit {
            anchors.left: printerName.right
            anchors.top: parent.top
            anchors.right: parent.right
            text: mainController.getPrinter()
            onTextChanged: {
                mainController.setPrinter(text)
            }
        }
    }

    Row {
        id: row2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: row1.bottom
        height:30
        anchors.margins: 0
        Text {
            id:ippayment
            width: 140
            anchors.left: parent.left
            anchors.top: parent.top
            text:"Cổng thanh toán:"
        }

        TextEdit {
            anchors.left: ippayment.right
            anchors.top: parent.top
            anchors.right: parent.right
            text:mainController.getPayment()
            onTextChanged: {
                mainController.setPayment(text)
            }
        }
    }
}
