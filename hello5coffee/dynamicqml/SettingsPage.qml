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
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

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

            onTelnetDone: {
                progressScan.updateVisible(false)
                telnetResult.updateTelnetResult(data)
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
                width: parent.width
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
                    width: parent.width
                    spacing: 40

                    Column {
                        width: (parent.width/3-10)
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
                        width: (parent.width/3-10)
                        Label {
                            text: "Config wifi DOCK"
                        }
                        TextField {
                            id: txtSSID
                            width: parent.width
                            placeholderText: "SSID"
                            Layout.fillWidth: true
                        }

                        TextField {
                            id: txtKey
                            width: parent.width
                            placeholderText: "Key"
                            Layout.fillWidth: true
                        }

                        Button {
                            enabled: (txtSSID.text !== "")
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
                            height: 100
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



                        TextEdit {
                            id: telnetResult
                            width: parent.width
                            height: 100
                            text: "telnet result"
                            focus: true

                            function updateTelnetResult(data) {
                                text = data
                            }
                        }

                        RowLayout {
                            TextField {
                                id: txtTHost
                                text: "113.161.67.179"
                                Layout.fillWidth: true
                            }
                            TextField {
                                id: txtTPort
                                text: "59101"
                                Layout.fillWidth: true
                            }
                        }

                        Button {
                            text:"Telnet"
                            onClicked: {
                                progressScan.updateVisible(true)
                                telnetResult.text = "Telnet result"
                                mainController.testTelnet(txtTHost.text, txtTPort.text)
                            }
                        }
                    }

                    Column {
                        width: (parent.width/3-10)
                        Label {
                            text: "Config wifi"
                        }
                        TextField {
                            width: parent.width
                            id: txtSSIDPi
                            placeholderText: "SSID"
                            Layout.fillWidth: true
                        }

                        TextField {
                            width: parent.width
                            id: txtKeyPi
                            placeholderText: "Key"
                            Layout.fillWidth: true
                        }

                        Button {
                            enabled: (txtSSIDPi.text !== "")
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
    }
}
