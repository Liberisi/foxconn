/****************************************************************************
** Meta object code from reading C++ file 'fid_cmc_socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fid_cmc_socket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fid_cmc_socket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FidCMCSocket_t {
    QByteArrayData data[6];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FidCMCSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FidCMCSocket_t qt_meta_stringdata_FidCMCSocket = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FidCMCSocket"
QT_MOC_LITERAL(1, 13, 14), // "on_socket_read"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "on_socket_connected"
QT_MOC_LITERAL(4, 49, 22), // "on_socket_disconnected"
QT_MOC_LITERAL(5, 72, 15) // "on_socket_error"

    },
    "FidCMCSocket\0on_socket_read\0\0"
    "on_socket_connected\0on_socket_disconnected\0"
    "on_socket_error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FidCMCSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FidCMCSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FidCMCSocket *_t = static_cast<FidCMCSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_socket_read(); break;
        case 1: _t->on_socket_connected(); break;
        case 2: _t->on_socket_disconnected(); break;
        case 3: _t->on_socket_error(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FidCMCSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FidCMCSocket.data,
      qt_meta_data_FidCMCSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FidCMCSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FidCMCSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FidCMCSocket.stringdata0))
        return static_cast<void*>(const_cast< FidCMCSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int FidCMCSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
