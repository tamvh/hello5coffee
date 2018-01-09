/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2015 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.1

Component {
    Pane {
        id: appContainer
        Connections {
            target: mainController
            onScanDockDone: {
                dockDevice.model = listDock

                progressScan.updateVisible(false)
                buttonScan.enabled = true
            }

            onDockConnectionChange: {
                btnActConnect.updateStatus(connected)
            }

            onPingDone: {
                progressScan.updateVisible(false)
                pingResult.updateResult(data)
            }

            onWifiStatusDone: {
                progressScan.updateVisible(false)
                wifiStatus.updateResult(data)
            }
        }

        Flickable {
            anchors.fill: parent
            contentHeight: column.height

            Column {
                id: column
                anchors.horizontalCenter: parent.horizontalCenter
                BusyIndicator {
                    id: progressScan
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: false

                    function updateVisible(show) {
                        visible = show
                    }
                }

                Row {
                    spacing: 40

                    Column {
                        spacing: 40

                        ColumnLayout {
                            RowLayout {
                                spacing: 10

                                Label {
                                    text: "Dock status:"
                                }

                                Label {
                                    id: dockStatus
                                    function updateStatus(connected) {
                                        if (connected) {
                                            text = "Connected ";
                                            color = "green"
                                        } else {
                                            text = "Disconnected ";
                                            color = "red"
                                        }
                                    }
                                }

                                Label {
                                    id: dockIP
                                    Component.onCompleted: {
                                        if (mainController.getDockServer() !== null) {
                                            text = mainController.getDockServer()
                                        } else {
                                            text = "Not configure"
                                        }
                                    }
                                }
                            }

                            Button {
                                id: btnActConnect
                                text: "Connect"

                                Component.onCompleted: {
                                    updateStatus(mainController.isConnected())
                                }

                                onClicked: {
                                    if (text === "Connect") {
                                        mainController.connectToDock(dockIP.text)
                                    } else {
                                        mainController.disconnectFromDock()
                                    }
                                }

                                function updateStatus(connected) {
                                    if (connected) {
                                        text = "Disconnect";
                                    } else {
                                        text = "Connect";
                                    }
                                    dockStatus.updateStatus(connected)
                                }
                            }

                            Button {
                                id: btnActRestart
                                text: "Restart dock service"

                                onClicked: {
                                    mainController.restartDock()
                                }

                            }
                        }

                        RowLayout {
                            spacing: 10

                            Label {
                                text: "Dock:"
                            }

                            ComboBox {
                                id: dockDevice
                                Layout.fillWidth: true
                                onCurrentTextChanged: {
                                    if (currentText !== "") {
                                        buttonConnect.enabled = true
                                    } else {
                                        buttonConnect.enabled = false
                                    }
                                }
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Button {
                                id: buttonScan
                                text:"Scan dock"
                                //backgroundColor: Theme.primaryColor
                                onClicked: {
                                    progressScan.updateVisible(true)
                                    buttonScan.enabled = false

                                    mainController.scanDock()
                                }
                            }

                            Button {
                                id: buttonConnect
                                text:"Connect"
                                enabled: false
                                //backgroundColor: Theme.primaryColor
                                onClicked: {
                                    if (mainController.connectToDock(dockDevice.currentText) === true) {
                                        dockIP.text = dockDevice.currentText
                                    }
                                }
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Button {
                                text:"Print test"
                                onClicked: {
                                    var foodItems;
                                    mainController.printTest(foodItems);
                                }
                            }

                            Button {
                                property bool readerRun: true
                                text: "Start reader"
                                //backgroundColor: Theme.primaryColor
                                onClicked: {
                                    if (!readerRun) {
                                        text = "Start reader"
                                    } else {
                                        text = "Stop reader"
                                    }

                                    mainController.testReaderDevice(readerRun)
                                    readerRun = !readerRun
                                }
                            }
                        }

                        Button {
                            text:"Back"
                            onClicked: {
                                stackView.pop()
                            }
                        }
                    }

                    Column {
                        Label {
                            text: "Config wifi DOCK"
                        }
                        TextField {
                            id: txtSSID
                            placeholderText: "SSID"
                            Layout.fillWidth: true
                        }

                        TextField {
                            id: txtKey
                            placeholderText: "Key"
                            Layout.fillWidth: true
                        }

                        Button {
                            text:"Update wifi"
                            onClicked: {
                                mainController.updateWifi(txtSSID.text, txtKey.text)
                            }
                        }

                        Button {
                            text:"Update wifi open"
                            onClicked: {
                                mainController.updateWifi(txtSSID.text, "empty", "open")
                            }
                        }

                        TextEdit {
                            id: pingResult
                            width: parent.width
                            height: 200
                            text: "Ping result"
                            focus: true

                            function updateResult(data) {
                                text = data
                            }
                        }

                        TextField {
                            id: txtHost
                            text: "8.8.8.8"
                            Layout.fillWidth: true
                        }

                        Button {
                            text:"Ping"
                            onClicked: {
                                progressScan.updateVisible(true)
                                pingResult.text = "Ping result"
                                mainController.testPing(txtHost.text)
                            }
                        }
                    }

                    Column {
                        Label {
                            text: "Config wifi"
                        }
                        TextField {
                            id: txtSSIDPi
                            placeholderText: "SSID"
                            Layout.fillWidth: true
                        }

                        TextField {
                            id: txtKeyPi
                            placeholderText: "Key"
                            Layout.fillWidth: true
                        }

                        Button {
                            text:"Update wifi"
                            onClicked: {
                                mainController.updateWifiPi(txtInterfaceName.text, txtSSIDPi.text, txtKeyPi.text)
                            }
                        }

                        TextEdit {
                            id: wifiStatus
                            width: parent.width
                            height: 200
                            text: "Wifi status"
                            focus: true

                            function updateResult(data) {
                                text = data
                            }
                        }

                        TextField {
                            id: txtInterfaceName
                            placeholderText: "Interface name"
                            Layout.fillWidth: true
                            text: "wlan0"
                        }

                        Button {
                            text:"Wifi status"
                            onClicked: {
                                progressScan.updateVisible(true)
                                pingResult.text = "Ping result"
                                mainController.wifiStatus(txtInterfaceName.text)
                            }
                        }

                        Button {
                            text:"Restart PI"
                            onClicked: {
                                mainController.restartPi()
                            }
                        }

                        Button {
                            text:"Halt PI"
                            onClicked: {
                                mainController.haltPi()
                            }
                        }
                    }

                }
            }
        }

        /*  Keyboard input panel.
            The keyboard is anchored to the bottom of the application.
        */
        InputPanel {
            id: inputPanel
            z: 99
            y: appContainer.height
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.left: parent.left
            //anchors.right: parent.right
            width: parent.width/2
            states: State {
                name: "visible"
                /*  The visibility of the InputPanel can be bound to the Qt.inputMethod.visible property,
                    but then the handwriting input panel and the keyboard input panel can be visible
                    at the same time. Here the visibility is bound to InputPanel.active property instead,
                    which allows the handwriting panel to control the visibility when necessary.
                */
                when: inputPanel.active
                PropertyChanges {
                    target: inputPanel
                    y: appContainer.height - inputPanel.height
                }
            }
            transitions: Transition {
                from: ""
                to: "visible"
                reversible: true
                ParallelAnimation {
                    NumberAnimation {
                        properties: "y"
                        duration: 250
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
}
