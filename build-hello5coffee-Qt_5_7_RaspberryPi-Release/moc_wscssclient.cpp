/****************************************************************************
** Meta object code from reading C++ file 'wscssclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../common/wscssclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wscssclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WsCssClient_t {
    QByteArrayData data[20];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WsCssClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WsCssClient_t qt_meta_stringdata_WsCssClient = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WsCssClient"
QT_MOC_LITERAL(1, 12, 9), // "connected"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "disconnected"
QT_MOC_LITERAL(4, 36, 19), // "textMessageReceived"
QT_MOC_LITERAL(5, 56, 3), // "msg"
QT_MOC_LITERAL(6, 60, 11), // "foundServer"
QT_MOC_LITERAL(7, 72, 2), // "ip"
QT_MOC_LITERAL(8, 75, 4), // "port"
QT_MOC_LITERAL(9, 80, 11), // "orderNumber"
QT_MOC_LITERAL(10, 92, 7), // "newData"
QT_MOC_LITERAL(11, 100, 8), // "onServer"
QT_MOC_LITERAL(12, 109, 3), // "ips"
QT_MOC_LITERAL(13, 113, 11), // "onConnected"
QT_MOC_LITERAL(14, 125, 8), // "onClosed"
QT_MOC_LITERAL(15, 134, 11), // "onReconnect"
QT_MOC_LITERAL(16, 146, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(17, 168, 7), // "message"
QT_MOC_LITERAL(18, 176, 4), // "ping"
QT_MOC_LITERAL(19, 181, 4) // "pong"

    },
    "WsCssClient\0connected\0\0disconnected\0"
    "textMessageReceived\0msg\0foundServer\0"
    "ip\0port\0orderNumber\0newData\0onServer\0"
    "ips\0onConnected\0onClosed\0onReconnect\0"
    "onTextMessageReceived\0message\0ping\0"
    "pong"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WsCssClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    1,   76,    2, 0x06 /* Public */,
       6,    2,   79,    2, 0x06 /* Public */,
       9,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   87,    2, 0x0a /* Public */,
      13,    0,   92,    2, 0x0a /* Public */,
      14,    0,   93,    2, 0x0a /* Public */,
      15,    0,   94,    2, 0x0a /* Public */,
      16,    1,   95,    2, 0x0a /* Public */,
      18,    0,   98,    2, 0x08 /* Private */,
      19,    2,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QVariant,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   12,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QByteArray,    2,    2,

       0        // eod
};

void WsCssClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WsCssClient *_t = static_cast<WsCssClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->textMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->foundServer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->orderNumber((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 5: _t->onServer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: _t->onConnected(); break;
        case 7: _t->onClosed(); break;
        case 8: _t->onReconnect(); break;
        case 9: _t->onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->ping(); break;
        case 11: _t->pong((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WsCssClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WsCssClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WsCssClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WsCssClient::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WsCssClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WsCssClient::textMessageReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WsCssClient::*_t)(const QString & , const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WsCssClient::foundServer)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (WsCssClient::*_t)(const QVariant & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WsCssClient::orderNumber)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject WsCssClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WsCssClient.data,
      qt_meta_data_WsCssClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WsCssClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WsCssClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WsCssClient.stringdata0))
        return static_cast<void*>(const_cast< WsCssClient*>(this));
    return QObject::qt_metacast(_clname);
}

int WsCssClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void WsCssClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void WsCssClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void WsCssClient::textMessageReceived(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WsCssClient::foundServer(const QString & _t1, const int & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WsCssClient::orderNumber(const QVariant & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
