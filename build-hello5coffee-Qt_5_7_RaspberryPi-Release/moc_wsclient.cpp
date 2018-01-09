/****************************************************************************
** Meta object code from reading C++ file 'wsclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hello5coffee/wsclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wsclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WSClient_t {
    QByteArrayData data[19];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WSClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WSClient_t qt_meta_stringdata_WSClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WSClient"
QT_MOC_LITERAL(1, 9, 9), // "connected"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 19), // "textMessageReceived"
QT_MOC_LITERAL(4, 40, 7), // "message"
QT_MOC_LITERAL(5, 48, 6), // "closed"
QT_MOC_LITERAL(6, 55, 9), // "reconnect"
QT_MOC_LITERAL(7, 65, 11), // "onConnected"
QT_MOC_LITERAL(8, 77, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(9, 99, 8), // "onClosed"
QT_MOC_LITERAL(10, 108, 11), // "onReConnect"
QT_MOC_LITERAL(11, 120, 13), // "onSessionDone"
QT_MOC_LITERAL(12, 134, 4), // "data"
QT_MOC_LITERAL(13, 139, 14), // "onSessionError"
QT_MOC_LITERAL(14, 154, 9), // "errorCode"
QT_MOC_LITERAL(15, 164, 12), // "errorMessage"
QT_MOC_LITERAL(16, 177, 7), // "onError"
QT_MOC_LITERAL(17, 185, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(18, 214, 5) // "error"

    },
    "WSClient\0connected\0\0textMessageReceived\0"
    "message\0closed\0reconnect\0onConnected\0"
    "onTextMessageReceived\0onClosed\0"
    "onReConnect\0onSessionDone\0data\0"
    "onSessionError\0errorCode\0errorMessage\0"
    "onError\0QAbstractSocket::SocketError\0"
    "error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WSClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       5,    0,   73,    2, 0x06 /* Public */,
       6,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   75,    2, 0x0a /* Public */,
       8,    1,   76,    2, 0x0a /* Public */,
       9,    0,   79,    2, 0x0a /* Public */,
      10,    0,   80,    2, 0x0a /* Public */,
      11,    1,   81,    2, 0x0a /* Public */,
      13,    2,   84,    2, 0x0a /* Public */,
      16,    1,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void WSClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WSClient *_t = static_cast<WSClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->textMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->closed(); break;
        case 3: _t->reconnect(); break;
        case 4: _t->onConnected(); break;
        case 5: _t->onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->onClosed(); break;
        case 7: _t->onReConnect(); break;
        case 8: _t->onSessionDone((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 9: _t->onSessionError((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
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
            typedef void (WSClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WSClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WSClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WSClient::textMessageReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WSClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WSClient::closed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WSClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WSClient::reconnect)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject WSClient::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WSClient.data,
      qt_meta_data_WSClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WSClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WSClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WSClient.stringdata0))
        return static_cast<void*>(const_cast< WSClient*>(this));
    return QThread::qt_metacast(_clname);
}

int WSClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void WSClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void WSClient::textMessageReceived(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WSClient::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void WSClient::reconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
