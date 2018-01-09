import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import MainController 1.0
import QmlDefine 1.0
import "dynamicqml"

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visibility: mainController.isDebugmode() ? "Maximized" : Window.FullScreen
    flags: mainController.isDebugmode() ? Qt.Window : Qt.FramelessWindowHint | Qt.Window
    visible: true

    property int globalPadding: 10
    property int fntsize: (mainController.getConfigBillItemFontsize() + 2)
    property int usrConfColwidth1: 220
    property int usrConfColwidth2: Screen.width - usrConfColwidth1 - 160
    property int admConfColwidth1: 220
    property int admConfColwidth2: 180
    property int settingFlags1: 0

    Material.primary: "#006493"
    Material.accent: "#006493"

    Component.onCompleted: {

    }

    header: ToolBar {
        Rectangle {
            anchors.fill: parent
            LinearGradient {
                anchors.fill: parent
                start: Qt.point(0, 0)
                end: Qt.point(parent.width, parent.height)

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#006493" }
                    GradientStop { position: 1.0; color: "#006493" }
                }

                RowLayout {
                    anchors.fill: parent

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
                        contentItem: Image {
                            fillMode: Image.Pad
                            horizontalAlignment: Image.AlignHCenter
                            verticalAlignment: Image.AlignVCenter
                            source: "qrc:/icons/icons/logo.png"
                        }
                        onClicked: {
                            idAboutPage.open();
                        }
                    }

                    FontLoader {
                        id: idFont
                        source: "qrc:/fonts/fonts/UnisectVnuBold.ttf"
                        name: "UnisectVnu"

                    }
                    RowLayout {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        Label {
                            id: lblTitle
                            text: "hello 5 coffee"
                            color: "white"
                            font.pixelSize: 30
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (toolBtnSetting.visible === true) {
                                        toolBtnSetting.visible = mainController.isDebugmode();
                                    }
                                    else {
                                        if (settingFlags1 === 5) {
                                            console.log('open setting');
                                            toolBtnSetting.visible = true
                                        }
                                    }
                                    settingFlags1 = 0
                                }
                            }
                        }
                    }


                    RowLayout {
                        id: controlBox
                        anchors.right: parent.right
                        anchors.rightMargin: 5
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
                                settingFlags1++
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
                            onClicked: {
                                optionsMenu.open()
                            }

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
                                    text: "Cài đặt Quầy hàng"
                                    onTriggered:  {
                                        stackView.push(settingPages2)
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

        initialItem: VposPage {
            onVisibleChanged: {
                if (visible) {
                    toolButtonBack.visible = false
                } else {
                    toolButtonBack.visible = true
                }
            }
        }
    }

    SettingPages {
        id: settingPages2
    }
}
