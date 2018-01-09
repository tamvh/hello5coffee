import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

// for test UI, delete this file ???

ApplicationWindow {
    id: idKitchen
    width: 800
    height: 600
    visible: true
    visibility: mainController.isDebugmode() ? "Maximized" : Window.FullScreen
    flags: mainController.isDebugmode() ? Qt.Window : Qt.FramelessWindowHint | Qt.Window

    property bool isShowSearch: false

    Material.primary: Material.DeepOrange
    Material.accent: Material.DeepOrange

    Component.onCompleted: {
        titleLabel.text = (mainController.getAppTitle() + " - Bếp");
    }

    header: ToolBar {
        Rectangle {
            anchors.fill: parent
            LinearGradient {
                anchors.fill: parent
                start: Qt.point(0, 0)
                end: Qt.point(parent.width, parent.height)

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#ad3906" }
                    GradientStop { position: 1.0; color: "#ef8422" }
                }

                RowLayout {
                    id: searchBox
                    anchors.fill: parent
                    visible: isShowSearch

                    Rectangle {
                        width: 3
                    }

                    ToolButton {
                        id: tbimg1
                        contentItem: Image {
                            fillMode: Image.Pad
                            horizontalAlignment: Image.AlignHCenter
                            verticalAlignment: Image.AlignVCenter
                            source: "qrc:/icons/icons/logo.png"
                        }
                    }

                    Rectangle {
                        anchors.left: tbimg1.right
                        width: parent.width - (tbimg1.width+tbimg2.width)*2
                        height: parent.height - 2
                        radius: parent.height/2
                        border.color: "#333"
                        border.width: 1

                        RowLayout {
                            ToolButton {
                                id: tbimg2
                                contentItem: Image {
                                    fillMode: Image.Stretch
                                    horizontalAlignment: Image.AlignHCenter
                                    verticalAlignment: Image.AlignVCenter
                                    source: "qrc:/icons/icons/search_back.png"
                                }
                                onClicked: {
                                    idSearchbox.text = ""
                                    isShowSearch = !isShowSearch
                                    mainController.uiFoodupdateStatus( isShowSearch ? -4 : 4)
                                }
                            }

                            Image {
                                anchors { top: parent.top; bottom: parent.bottom; right: parent.right; margins: 1 }
                                id: clearText
                                fillMode: Image.Pad
                                smooth: true
                                visible: (idSearchbox.text != "")
                                source: "qrc:/icons/icons/delete.png"
                                height: parent.height //- platformStyle.paddingMedium * 2
                                width: parent.height //- platformStyle.paddingMedium * 2

                                MouseArea {
                                    id: clear
                                    anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter }
                                    height: idSearchbox.height; width: idSearchbox.height
                                    onClicked: {
                                        idSearchbox.text = ""
                                        idSearchbox.forceActiveFocus()
                                    }
                                }
                            }

                            Timer {
                                id: idTimer
                                interval: 90000 //90000 = 90 seconds to clear search-filter
                                running: false
                                repeat: false
                                onTriggered: searchFilter = ""
                            }

                            TextField {
                                id: idSearchbox
                                anchors.left: tbimg2.right
                                anchors.right: clearText.left
                                placeholderText: mainController.getConfigSearchadvance() ? "Tên ... hoặc các ký tự đầu, ví dụ bb = Bún Bò" : "Gõ tên ..."
                                text: ""
                                color: "black"
                                focus: true

                                onVisibleChanged: {
                                    if (visible)
                                        placeholderText = mainController.getConfigSearchadvance() ? "Tên ... hoặc các ký tự đầu, ví dụ bb = Bún Bò" : "Gõ tên ..."
                                }

                                onDisplayTextChanged: {
                                    var srchtxt = mainController.viet2latin(text);
                                    if (searchFilter !== srchtxt)
                                    {
                                        searchFilter = srchtxt;
                                        mainController.searchFood(searchFilter);

                                        idTimer.restart()
                                    }
                                }
                            }
                        }
                    }
                }

                RowLayout {
                    anchors.fill: parent
                    visible: !isShowSearch

                    ToolButton {
                        id: toolButtonBack
                        visible: false
                        contentItem: Image {
                            fillMode: Image.Pad
                            horizontalAlignment: Image.AlignHCenter
                            verticalAlignment: Image.AlignVCenter
                            source: "qrc:/icons/icons/ic_arrow_back_white_24px.svg"
                        }
                        onClicked: {
                            stackView.pop()
                        }
                    }

                    Rectangle {
                        width: 3
                    }

                    ToolButton {
                        id: vposButton
                        property int settingFlags1: 0
                        property int settingFlags2: 0
                        contentItem: Image {
                            fillMode: Image.Pad
                            horizontalAlignment: Image.AlignHCenter
                            verticalAlignment: Image.AlignVCenter
                            source: "qrc:/icons/icons/logo.png"
                        }
                        onClicked: {
                            if (toolBtnSetting.visible === true) {
                                toolBtnSetting.visible = mainController.isDebugmode();
                            }
                            else {
                                if ((settingFlags1 > 0) && ((settingFlags1 + 1) ==  settingFlags2)) {
                                    toolBtnSetting.visible = true
                                }

                                settingFlags1 = 0
                                settingFlags2 = 0
                            }
                        }
                    }

                    FontLoader {
                        id: idFont
                        source: "qrc:/fonts/fonts/UnisectVnuBold.ttf"
                        name: "UnisectVnu"

                    }

                    Label {
                        id: titleLabel
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        Layout.fillWidth: true
                        color: "white"
                        font.pixelSize: 25
                        font.family: idFont.name
                        text: "NONAME"

                        Connections {
                            target: mainController
                            onUpdateTitle: {
                                titleLabel.text = title
                            }
                        }
                    }

                    RowLayout {
                        id: controlBox
                        ToolButton {
                            ToolTip.visible: pressed
                            ToolTip.text: "Tìm kiếm món ăn"
                            ToolTip.timeout: 2000
                            contentItem: Image {
                                fillMode: Image.Pad
                                horizontalAlignment: Image.AlignHCenter
                                verticalAlignment: Image.AlignVCenter
                                source: "qrc:/icons/icons/search_white.png"
                            }
                            onClicked: {
                                idSearchbox.text = ""
                                idSearchbox.focus = true
                                isShowSearch = !isShowSearch
                                mainController.uiFoodupdateStatus( isShowSearch ? -4 : 4)
                            }
                        }

                        ToolButton {
                            id: toolButtonCloud
                            ToolTip.visible: pressed
                            ToolTip.text: "Trạng thái kết nối đến máy chủ VPOS"
                            ToolTip.timeout: 3000

                            contentItem: Image {
                                id: imageCloudStatus
                                fillMode: Image.Pad
                                horizontalAlignment: Image.AlignHCenter
                                verticalAlignment: Image.AlignVCenter
                                source: "qrc:/icons/icons/ic_cloud_queue_white_24px.svg"

                                Connections {
                                    target: mainController
                                    onCloudConnectionChange: {
                                        imageCloudStatus.updateStatus(connected)
                                    }
                                }

                                function updateStatus(connected) {
                                    if (connected) {
                                        source = "qrc:/icons/icons/ic_cloud_done_white_24px.svg"
                                    } else {
                                        source = "qrc:/icons/icons/ic_cloud_off_white_24px.svg"
                                    }
                                }
                            }

                            onClicked: {
                                vposButton.settingFlags1++
                            }
                        }

                        ToolButton {
                            id: toolButtonDock

                            ToolTip.visible: pressed
                            ToolTip.text: "Trạng thái kết nối đến thiết bị"
                            ToolTip.timeout: 3000

                            contentItem: Image {
                                id: imageDockStatus
                                fillMode: Image.Pad
                                horizontalAlignment: Image.AlignHCenter
                                verticalAlignment: Image.AlignVCenter

                                Component.onCompleted: {
                                    updateStatus(mainController.isConnected())
                                }

                                Connections {
                                    target: mainController
                                    onDockConnectionChange: {
                                        imageDockStatus.updateStatus(connected)

                                        if (connected)  {
                                            appMessage.showMessage("Đã kết nối đến thiết bị")
                                        } else {
                                            appMessage.showMessage("Mất kết nối đển thiết bị")
                                        }
                                    }
                                }

                                function updateStatus(connected) {
                                    if (connected) {
                                        source = "qrc:/icons/icons/ic_signal_wifi_4_bar_white_24px.svg"
                                    } else {
                                        source = "qrc:/icons/icons/ic_signal_wifi_off_white_24px.svg"
                                    }
                                }
                            }

                            onClicked: {
                                if (vposButton.settingFlags1===0) {
                                    mainController.scanDock(true);
                                }
                                vposButton.settingFlags2++
                            }
                        }

                        ToolButton {
                            id: toolBtnSetting
                            visible: mainController.isDebugmode()
                            contentItem: Image {
                                fillMode: Image.Pad
                                horizontalAlignment: Image.AlignHCenter
                                verticalAlignment: Image.AlignVCenter
                                source: "qrc:/icons/icons/menu.png"
                            }
                            onClicked: optionsMenu.open()

                            Menu {
                                id: optionsMenu
                                x: parent.width - width
                                transformOrigin: Menu.TopRight

                                MenuItem {
                                    text: "Cài đặt Thiết bị"
                                    onTriggered:  {
                                        stackView.push(settingPage)
                                    }
                                }
                                MenuItem {
                                    text: "Cấu hình Quầy hàng"
                                    onTriggered:  {
                                        stackView.push(settingPages2)
                                    }
                                }
                                MenuItem {
                                    text: "Cập nhật menu ngay"
                                    onTriggered: {
                                        mainController.checkUpdateFoodData()
                                    }
                                }
                                MenuItem {
                                    text: "Thông tin ứng dụng"
                                    onTriggered: {
                                        systemDialog.open()
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: KitchenPage {
            onVisibleChanged: {
                if (visible) {
                    console.log("Kitchen page visible")
                    toolButtonBack.visible = false
                    userConfigButtonVisible = mainController.getUserEnableConfig()
                } else {
                    console.log("Kitchen page disible")
                    toolButtonBack.visible = true
                    userConfigButtonVisible = false
                }
            }
        }
    }

    ToolTip {
        id: appMessage
        timeout: 2000
        x: (parent.width - width) / 2
        y: parent.height / 3

        function showMessage(msg) {
            text = msg
            open()
        }
    }
}
