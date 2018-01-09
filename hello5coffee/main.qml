import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

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
}
