import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.1
import QtQuick.VirtualKeyboard.Settings 2.1

import MainController 1.0
import QmlDefine 1.0
import "dynamicqml"

VPOSWindow {
    id: window

    MainController {
        id: mainController
    }

    QmlDefine {
        id: qmlDefine
    }

    SettingsPage {
        id: settingPage
    }

    /*  Keyboard input panel.
        The keyboard is anchored to the bottom of the application.
    */
    InputPanel {
        id: inputPanel
        z: 99
        y: window.height
        anchors.horizontalCenter: parent.horizontalCenter
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
                y: window.height - inputPanel.height
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
