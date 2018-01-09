TEMPLATE = app

QT += qml quick quickcontrols2 concurrent svg network websockets printsupport xml core
CONFIG += link_pkgconfig
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}
#App versioning
VERSION_MAJOR = 1
VERSION_MINOR = 6
VERSION_BUILD = 2

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
DEFINES += APP_VER=\\\"$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}\\\"

CONFIG += c++11


DEFINES += REAL_VERSION

SOURCES += main.cpp \
    http/json.cpp \
    http/httptool.cpp \
    http/httpparams.cpp \
    http/httpbase.cpp \
    http/httpbase2.cpp \
    ../common/prntdataformat.cpp \
    ../common/configsetting.cpp \
    ../common/deviceclient.cpp \
    ../common/deviceclientservice.cpp \
    ../common/udpbrdcastclient.cpp \
    ../common/wscssclient.cpp \
    maincontroller.cpp \
    billdetail.cpp \
    commonfunction.cpp \
    wsclient.cpp \
    qmldefine.cpp \
    functionutils.cpp \
    ../common/utility.cpp

RESOURCES += qml.qrc

linux-rpi3-g++ {
    QTPLUGIN += qtvirtualkeyboardplugin
    DEFINES += USE_VT_KB
    DEFINES += ALLOW_LOCAL_DOCK
    DEFINES += USE_SYSLOG
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

include(qrencode-3.4.4/qrencode.pri)
INCLUDEPATH += $$PWD/qrencode-3.4.4
DEFINES += HAVE_CONFIG_H

HEADERS += \
    http/json.h \
    http/httptool.h \
    http/httpparams.h \
    http/httpbase.h \
    http/httpbase2.h \
    ../common/prntdataformat.h \
    ../common/configsetting.h \
    ../common/deviceclient.h \
    ../common/deviceclientservice.h \
    ../common/udpbrdcastclient.h \
    ../common/wscssclient.h \
    maincontroller.h \
    commonfunction.h \
    wsclient.h \
    billdetail.h \
    qmldefine.h \
    json/json.hpp \
    functionutils.h \
    json/androidndkworkaround.h \
    ../common/utility.h

android {
    QT += androidextras
}

RESOURCES += icons/icons.qrc
RC_FILE = VPOS.rc

DISTFILES += \
    fonts/UnisectVnu Black.ttf \
    fonts/UnisectVnu Bold.ttf \
    fonts/UnisectVnu Bold.ttf \
    fonts/UnisectVnu Black.ttf \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    images/foods/classic/saigon_supreme.jpg \
    images/foods/classic/tamarind_chicken.jpg \
    images/foods/classic/teriyaki_chicken.jpg \
    images/foods/classic/ultimate_hawallan.jpg \
    images/foods/classic/veggie_mania.jpg \
    images/foods/premium/EXTRAVAGANZZA.jpg \
    images/foods/premium/MEAT LOVERS.jpg \
    images/foods/premium/OCEAN MANIA.jpg \
    images/foods/premium/SEAFOOD DELIGHT.jpg \
    images/foods/premium/SURF AND TURF.jpg

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
