import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Pane {
    id:appconfigPage
    property int col1width: 100
    property int col2width: 250

    Flickable {
        anchors.fill: parent
        contentHeight: configColumn.height

        Column {
            id: configColumn
            width: parent.width
            spacing: globalPadding

            GroupBox {
                title: "CÀI ĐẶT MÁY CHỦ VÀ THIẾT BỊ"
                width: parent.width

                Column {
                    spacing: 10

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Row {
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                width: admConfColwidth1
                                anchors.verticalCenter: parent.verticalCenter
                                text: "-   List Phone:"
                            }
                            RowLayout {
                                width: admConfColwidth2 * 5
                                TextField {
                                    id: idlistPhone
                                    placeholderText: "0935954858"
                                    width: admConfColwidth2 * 5
                                    Layout.fillWidth: true
                                    text: mainController.getListPhone()
                                    onEditingFinished: {
                                        mainController.setListPhone(text)
                                    }
                                }
                            }
                        }
                        Row {
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                width: admConfColwidth1
                                anchors.verticalCenter: parent.verticalCenter
                                text: "-   List Email:"
                            }
                            RowLayout {
                                width: admConfColwidth2 * 5
                                TextField {
                                    id: idlistEmail
                                    placeholderText: "tamvh@vng.com.vn, diepdt@vng.com.vn"
                                    width: admConfColwidth2 * 5
                                    Layout.fillWidth: true
                                    text: mainController.getListEmail()
                                    onEditingFinished: {
                                        mainController.setListEmail(text)
                                    }
                                }
                            }

                        }

                        Row {
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                width: admConfColwidth1
                                anchors.verticalCenter: parent.verticalCenter
                                text: "-   Máy chủ VPOS:"
                            }
                            TextField {
                                id: idServerUrl
                                placeholderText: "vpos.zing.vn/vpos"
                                width: admConfColwidth2 * 5
                                Layout.fillWidth: true
                                text: mainController.getPayment()
                                onEditingFinished: {
                                    mainController.setPayment(text)
                                }
                            }
                        }

                        Row {
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                width: admConfColwidth1
                                anchors.verticalCenter: parent.verticalCenter
                                text: "-   Trans Protocol: "
                            }
                            ComboBox {
                                id: idTransProtocol
                                width: admConfColwidth2
                                Layout.fillWidth: true
                                model: ListModel {
                                    id: cbTranspro
                                    ListElement { text: "HTTP / WS"; transpro: "http"}
                                    ListElement { text: "HTTPS / WSS"; transpro: "https"}
                                }
                                textRole: "text"
                                currentIndex: mainController.getTransferProtocol() === "https"
                                onCurrentIndexChanged: {
                                    mainController.setTransferProtocol(cbTranspro.get(currentIndex).transpro)
                                }
                            }
                        }

                        Row {
                            visible: mainController.isDebugmode()
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                width: admConfColwidth1
                                anchors.verticalCenter: parent.verticalCenter
                                text: "-   Dock version: "
                            }

                            ComboBox {
                                width: admConfColwidth2
                                Layout.fillWidth: true
                                model: ListModel {
                                    id: cbItems
                                    ListElement { text: "1.0" }
                                    ListElement { text: "2.0" }
                                }
                                currentIndex: mainController.getConfigDockversion() === "1.0" ? 0 : 1

                                onCurrentIndexChanged: {
                                    mainController.setConfigDockversion(cbItems.get(currentIndex).text)
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 10

                        Row {
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                width: admConfColwidth1
                                anchors.verticalCenter: parent.verticalCenter
                                text: "-   Local IP:"
                            }

                            TextField {
                                id: idLocalIp
                                enabled: false
                                width: admConfColwidth2 * 5
                                Layout.fillWidth: true
                                text: mainController.getLocalIp();
                            }
                        }

                        Row {
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                width: admConfColwidth1
                                anchors.verticalCenter: parent.verticalCenter
                                text: "-   Printer size: "
                            }

                            ComboBox {
                                width: admConfColwidth2
                                Layout.fillWidth: true
                                model: ListModel {
                                    id: cbPageItem
                                    ListElement { text: "small" }
                                    ListElement { text: "large" }
                                }
                                currentIndex: mainController.getConfigPrintersize() === "small" ? 0 : 1

                                onCurrentIndexChanged: {
                                    mainController.setConfigPrintersize(cbPageItem.get(currentIndex).text)
                                }
                            }
                        }
                    }
                }
            }

            GroupBox {
                title: "CÀI ĐẶT QUẦY HÀNG (User Config)"
                width: parent.width

                onVisibleChanged: {
                    if (visible) {
                        idMerchantID.text = mainController.getAppName()
                        idAppTitle.text = mainController.getAppTitle()
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true

                    Row {
                        Layout.fillWidth: true
                        spacing: 10
                        Label {
                            width: usrConfColwidth1
                            anchors.verticalCenter: parent.verticalCenter
                            text: "-   Mã quầy hàng : "
                        }
                        TextField {
                            id: idMerchantID
                            placeholderText: "vpos"
                            text: mainController.getAppName()
                            width: admConfColwidth2
                            onEditingFinished: {
                                // need check appname/merchantID from server and show valid alert msg ...
                                mainController.setAppName(text)
                            }
                        }
                    }

                    Row {
                        Layout.fillWidth: true
                        spacing: 10
                        Label {
                            width: usrConfColwidth1
                            anchors.verticalCenter: parent.verticalCenter
                            text: "-   Tên quầy hàng : "
                        }
                        TextField {
                            id: idAppTitle
                            text: mainController.getAppTitle()
                            placeholderText: "TÊN QUẦY HÀNG"
                            width: admConfColwidth2
                            onEditingFinished: {
                                mainController.setAppTitle(text)
                            }
                        }
                    }

                    Row {
                        Layout.fillWidth: true
                        spacing: 10

                        Button {
                            id: idButInhoadon
                            text: "In thử Hóa đơn"
                            onClicked: {
                                mainController.printTest("");
                            }
                        }
                    }

                    Row {
                        spacing: 10
                        Label {
                            width: usrConfColwidth1
                            anchors.verticalCenter: parent.verticalCenter
                            text: "-   Số bản in hóa đơn (1..5) : "
                        }

                        TextField {
                            id:idSobanin
                            text: mainController.getConfigSobanin();
                            width: 60
                            onEditingFinished: {
                                var num = parseInt(text);
                                mainController.setConfigSobanin(num);

                                // cập nhật tên bản in theo số lượng bản in
                                text = mainController.getConfigSobanin();
                                idTenbanin.text = mainController.getConfigTenbanin()
                            }
                        }
                    }

                    Row {
                        spacing: 10
                        Layout.fillWidth: true
                        Label {
                            width: usrConfColwidth1
                            anchors.verticalCenter: parent.verticalCenter
                            text: "-   Tên bản in : "
                        }

                        TextField {
                            id:idTenbanin
                            enabled: (parseInt(idSobanin.text) > 1)
                            width: usrConfColwidth2
                            text: mainController.getConfigTenbanin();
                            onEditingFinished: {
                                mainController.setConfigTenbanin(text);

                                // lấy lại tên bản in sau khi cập nhật
                                text = mainController.getConfigTenbanin();
                            }
                        }
                    }

                    Row {
                        spacing: 10
                        Layout.fillWidth: true
                        Label {
                            width: usrConfColwidth1
                            anchors.verticalCenter: parent.verticalCenter
                            text: " "
                        }

                        Label {
                            anchors.verticalCenter: parent.verticalCenter
                            Layout.fillWidth: true
                            enabled: false
                            text: "Tên bản in cách nhau bằng dấu ';' từ 2 bản in trở lên tên bản in mới được in ra"
                        }
                    }

                    Row {
                        spacing: 10
                        Layout.fillWidth: true
                        Label {
                            width: usrConfColwidth1
                            anchors.verticalCenter: parent.verticalCenter
                            text: "-   Thông tin (đầu) hóa đơn : "
                        }

                        TextField {
                            id:idBillInfo
                            width: usrConfColwidth2
                            text: mainController.getConfigBillPreinf()
                            placeholderText: "Thông tin địa chỉ số điện thoại ... ';' để xuống dòng"
                            onEditingFinished: {
                                mainController.setConfigBillPreinf(text);

                                // lấy lại tên bản in sau khi cập nhật
                                text = mainController.getConfigBillPreinf();
                            }
                        }
                    }

                    Row {
                        spacing: 10
                        Layout.fillWidth: true
                        Label {
                            width: usrConfColwidth1
                            anchors.verticalCenter: parent.verticalCenter
                            text: "-   Thông tin (cuối) hóa đơn : "
                        }

                        TextField {
                            id:idBillInfoLast
                            width: usrConfColwidth2
                            text: mainController.getConfigBillPostinf()
                            placeholderText: "Cảm ơn Quí khách, hẹn gặp lại ... ';' để xuống dòng"
                            onEditingFinished: {
                                mainController.setConfigBillPostinf(text);

                                // lấy lại tên bản in sau khi cập nhật
                                text = mainController.getConfigBillPostinf();
                            }
                        }
                    }
                }
            }

            GroupBox {
                title: "Vpos Application"
                width: parent.width

                Column {
                    spacing: 10
                    Column {
                        visible: true //mainController.isRaspberry();
                        spacing: 10
                        Label {
                            text: "Lập lịch reboot Pi.  Vpos khởi động lúc: " + mainController.getRestartTime();
                        }

                        Label {
                            id: idlabtime
                        }

                        Timer  {
                            id: elapsedTimer
                            interval: 1000;
                            running: true;
                            repeat: true;

                            property bool timerswitch: true

                            onTriggered: {
                                idlabtime.text = "Giờ hệ thống: " + mainController.getCurrentTime(timerswitch);
                                timerswitch = !timerswitch;
                            }
                        }

                        ListView {
                            width: parent.width
                            height: contentHeight
                            spacing: 10
                            model: ListModel {
                                ListElement { number: 0; name: "Chủ Nhật" }
                                ListElement { number: 1; name: "Thứ Hai" }
                                ListElement { number: 2; name: "Thứ Ba" }
                                ListElement { number: 3; name: "Thứ Tư" }
                                ListElement { number: 4; name: "Thứ Năm" }
                                ListElement { number: 5; name: "Thứ Sáu" }
                                ListElement { number: 6; name: "Thứ Bảy" }
                            }

                            delegate: Component {
                                Row {
                                    width: 100
                                    height: 30
                                    CheckBox {
                                        height: parent.height
                                        checked: (mainController.getConfigRebootDatePi() & (1<<number));
                                        text: name
                                        onCheckedChanged: mainController.setConfigRebootDatePi(number, checked);
                                    }
                                }
                            }
                        }

                        Row {
                            height: 40
                            spacing: 10
                            Label {
                                height: parent.height
                                verticalAlignment: Qt.AlignVCenter
                                text: "Reboot vào lúc:" }

                            TextField {
                                height: parent.height
                                width: 40
                                verticalAlignment: Qt.AlignVCenter
                                horizontalAlignment: Qt.AlignHCenter
                                text: mainController.getConfigRebootTimePi(1);
                                onEditingFinished: {
                                    mainController.setConfigRebootTimePi(parseInt(text), 1);
                                    text = mainController.getConfigRebootTimePi(1);
                                    idrebootMinute.text = mainController.getConfigRebootTimePi(2);
                                }
                            }

                            Label {
                                height: parent.height
                                verticalAlignment: Qt.AlignVCenter
                                text: "giờ" }

                            TextField {
                                id: idrebootMinute
                                height: parent.height
                                width: 40
                                verticalAlignment: Qt.AlignVCenter
                                horizontalAlignment: Qt.AlignHCenter
                                text: mainController.getConfigRebootTimePi(2);
                                onEditingFinished: {
                                    mainController.setConfigRebootTimePi(parseInt(text), 2);
                                    text = mainController.getConfigRebootTimePi(2);
                                }
                            }

                            Label {
                                height: parent.height
                                verticalAlignment: Qt.AlignVCenter
                                text: "phút   ( chọn từ 00:03 . . 23:56 )" }
                        }
                    }

                    Button {
                        text: "Lưu cấu hình"
                        onClicked: {
                            mainController.saveConfig();
                        }
                    }

                    Button {
                        text: "Thoát chương trình"
                        onClicked: {
                            mainController.appQuit();
                        }
                    }
                }
            }
        }
    }
}
