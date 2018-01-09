/****************************************************************************
** Meta object code from reading C++ file 'deviceclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../common/deviceclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deviceclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DeviceClient_t {
    QByteArrayData data[48];
    char stringdata0[596];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceClient_t qt_meta_stringdata_DeviceClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DeviceClient"
QT_MOC_LITERAL(1, 13, 17), // "connectionChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "status"
QT_MOC_LITERAL(4, 39, 9), // "printDone"
QT_MOC_LITERAL(5, 49, 7), // "errcode"
QT_MOC_LITERAL(6, 57, 11), // "invoiceCode"
QT_MOC_LITERAL(7, 69, 19), // "printerReadyChanged"
QT_MOC_LITERAL(8, 89, 5), // "ready"
QT_MOC_LITERAL(9, 95, 11), // "mifareFound"
QT_MOC_LITERAL(10, 107, 6), // "mfdata"
QT_MOC_LITERAL(11, 114, 14), // "dockStatistics"
QT_MOC_LITERAL(12, 129, 4), // "stat"
QT_MOC_LITERAL(13, 134, 29), // "discoverDeviceServerBroadcast"
QT_MOC_LITERAL(14, 164, 12), // "QHostAddress"
QT_MOC_LITERAL(15, 177, 11), // "hostAddress"
QT_MOC_LITERAL(16, 189, 20), // "QList<QHostAddress>&"
QT_MOC_LITERAL(17, 210, 6), // "server"
QT_MOC_LITERAL(18, 217, 15), // "connectToServer"
QT_MOC_LITERAL(19, 233, 5), // "strIp"
QT_MOC_LITERAL(20, 239, 20), // "disconnectFromServer"
QT_MOC_LITERAL(21, 260, 21), // "getDeviceCapabilities"
QT_MOC_LITERAL(22, 282, 7), // "quint8&"
QT_MOC_LITERAL(23, 290, 12), // "capabilities"
QT_MOC_LITERAL(24, 303, 14), // "getPrinterList"
QT_MOC_LITERAL(25, 318, 11), // "listPrinter"
QT_MOC_LITERAL(26, 330, 5), // "print"
QT_MOC_LITERAL(27, 336, 7), // "printer"
QT_MOC_LITERAL(28, 344, 6), // "ivcode"
QT_MOC_LITERAL(29, 351, 4), // "data"
QT_MOC_LITERAL(30, 356, 3), // "tpl"
QT_MOC_LITERAL(31, 360, 17), // "startReaderDevice"
QT_MOC_LITERAL(32, 378, 16), // "stopReaderDevice"
QT_MOC_LITERAL(33, 395, 10), // "updateWifi"
QT_MOC_LITERAL(34, 406, 4), // "ssid"
QT_MOC_LITERAL(35, 411, 3), // "key"
QT_MOC_LITERAL(36, 415, 7), // "encrypt"
QT_MOC_LITERAL(37, 423, 14), // "restartService"
QT_MOC_LITERAL(38, 438, 18), // "checkPrinterStatus"
QT_MOC_LITERAL(39, 457, 11), // "isConnected"
QT_MOC_LITERAL(40, 469, 7), // "onError"
QT_MOC_LITERAL(41, 477, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(42, 506, 11), // "socketError"
QT_MOC_LITERAL(43, 518, 11), // "onConnected"
QT_MOC_LITERAL(44, 530, 11), // "onReadyRead"
QT_MOC_LITERAL(45, 542, 26), // "onApplicationStatusChanged"
QT_MOC_LITERAL(46, 569, 20), // "Qt::ApplicationState"
QT_MOC_LITERAL(47, 590, 5) // "state"

    },
    "DeviceClient\0connectionChanged\0\0status\0"
    "printDone\0errcode\0invoiceCode\0"
    "printerReadyChanged\0ready\0mifareFound\0"
    "mfdata\0dockStatistics\0stat\0"
    "discoverDeviceServerBroadcast\0"
    "QHostAddress\0hostAddress\0QList<QHostAddress>&\0"
    "server\0connectToServer\0strIp\0"
    "disconnectFromServer\0getDeviceCapabilities\0"
    "quint8&\0capabilities\0getPrinterList\0"
    "listPrinter\0print\0printer\0ivcode\0data\0"
    "tpl\0startReaderDevice\0stopReaderDevice\0"
    "updateWifi\0ssid\0key\0encrypt\0restartService\0"
    "checkPrinterStatus\0isConnected\0onError\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "onConnected\0onReadyRead\0"
    "onApplicationStatusChanged\0"
    "Qt::ApplicationState\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  139,    2, 0x06 /* Public */,
       4,    2,  142,    2, 0x06 /* Public */,
       7,    1,  147,    2, 0x06 /* Public */,
       9,    1,  150,    2, 0x06 /* Public */,
      11,    1,  153,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,  156,    2, 0x0a /* Public */,
      13,    1,  161,    2, 0x0a /* Public */,
      18,    1,  164,    2, 0x0a /* Public */,
      18,    1,  167,    2, 0x0a /* Public */,
      18,    0,  170,    2, 0x0a /* Public */,
      20,    0,  171,    2, 0x0a /* Public */,
      21,    1,  172,    2, 0x0a /* Public */,
      24,    1,  175,    2, 0x0a /* Public */,
      26,    4,  178,    2, 0x0a /* Public */,
      31,    1,  187,    2, 0x0a /* Public */,
      32,    0,  190,    2, 0x0a /* Public */,
      33,    3,  191,    2, 0x0a /* Public */,
      37,    0,  198,    2, 0x0a /* Public */,
      38,    0,  199,    2, 0x0a /* Public */,
      11,    0,  200,    2, 0x0a /* Public */,
      39,    0,  201,    2, 0x0a /* Public */,
      40,    1,  202,    2, 0x08 /* Private */,
      43,    0,  205,    2, 0x08 /* Private */,
      44,    0,  206,    2, 0x08 /* Private */,
      45,    1,  207,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,

 // slots: parameters
    QMetaType::Short, 0x80000000 | 14, 0x80000000 | 16,   15,   17,
    QMetaType::Short, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   27,   28,   29,   30,
    QMetaType::Void, QMetaType::QByteArray,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   34,   35,   36,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 46,   47,

       0        // eod
};

void DeviceClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeviceClient *_t = static_cast<DeviceClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->printDone((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->printerReadyChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->mifareFound((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->dockStatistics((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { qint16 _r = _t->discoverDeviceServerBroadcast((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< QList<QHostAddress>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = _r; }  break;
        case 6: { qint16 _r = _t->discoverDeviceServerBroadcast((*reinterpret_cast< QList<QHostAddress>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = _r; }  break;
        case 7: _t->connectToServer((*reinterpret_cast< const QHostAddress(*)>(_a[1]))); break;
        case 8: _t->connectToServer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->connectToServer(); break;
        case 10: _t->disconnectFromServer(); break;
        case 11: _t->getDeviceCapabilities((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->getPrinterList((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->print((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 14: _t->startReaderDevice((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 15: _t->stopReaderDevice(); break;
        case 16: _t->updateWifi((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 17: _t->restartService(); break;
        case 18: _t->checkPrinterStatus(); break;
        case 19: _t->dockStatistics(); break;
        case 20: { bool _r = _t->isConnected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 22: _t->onConnected(); break;
        case 23: _t->onReadyRead(); break;
        case 24: _t->onApplicationStatusChanged((*reinterpret_cast< Qt::ApplicationState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DeviceClient::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeviceClient::connectionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DeviceClient::*_t)(quint16 , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeviceClient::printDone)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DeviceClient::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeviceClient::printerReadyChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DeviceClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeviceClient::mifareFound)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (DeviceClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeviceClient::dockStatistics)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject DeviceClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DeviceClient.data,
      qt_meta_data_DeviceClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DeviceClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceClient.stringdata0))
        return static_cast<void*>(const_cast< DeviceClient*>(this));
    return QObject::qt_metacast(_clname);
}

int DeviceClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void DeviceClient::connectionChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeviceClient::printDone(quint16 _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeviceClient::printerReadyChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DeviceClient::mifareFound(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DeviceClient::dockStatistics(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
