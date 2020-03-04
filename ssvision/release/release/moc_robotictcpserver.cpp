/****************************************************************************
** Meta object code from reading C++ file 'robotictcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../robotictcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robotictcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ssvision__RoboticTCPServer_t {
    QByteArrayData data[10];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ssvision__RoboticTCPServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ssvision__RoboticTCPServer_t qt_meta_stringdata_ssvision__RoboticTCPServer = {
    {
QT_MOC_LITERAL(0, 0, 26), // "ssvision::RoboticTCPServer"
QT_MOC_LITERAL(1, 27, 15), // "readData_signal"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 17), // "disConnect_signal"
QT_MOC_LITERAL(4, 62, 27), // "newConnectIPportInfo_signal"
QT_MOC_LITERAL(5, 90, 2), // "ip"
QT_MOC_LITERAL(6, 93, 4), // "port"
QT_MOC_LITERAL(7, 98, 15), // "newConnect_slot"
QT_MOC_LITERAL(8, 114, 15), // "disConnect_slot"
QT_MOC_LITERAL(9, 130, 13) // "readData_slot"

    },
    "ssvision::RoboticTCPServer\0readData_signal\0"
    "\0disConnect_signal\0newConnectIPportInfo_signal\0"
    "ip\0port\0newConnect_slot\0disConnect_slot\0"
    "readData_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ssvision__RoboticTCPServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    0,   47,    2, 0x06 /* Public */,
       4,    2,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   53,    2, 0x0a /* Public */,
       8,    0,   54,    2, 0x0a /* Public */,
       9,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ssvision::RoboticTCPServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RoboticTCPServer *_t = static_cast<RoboticTCPServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readData_signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->disConnect_signal(); break;
        case 2: _t->newConnectIPportInfo_signal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->newConnect_slot(); break;
        case 4: _t->disConnect_slot(); break;
        case 5: _t->readData_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RoboticTCPServer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RoboticTCPServer::readData_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RoboticTCPServer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RoboticTCPServer::disConnect_signal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (RoboticTCPServer::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RoboticTCPServer::newConnectIPportInfo_signal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ssvision::RoboticTCPServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ssvision__RoboticTCPServer.data,
      qt_meta_data_ssvision__RoboticTCPServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ssvision::RoboticTCPServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ssvision::RoboticTCPServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ssvision__RoboticTCPServer.stringdata0))
        return static_cast<void*>(const_cast< RoboticTCPServer*>(this));
    return QObject::qt_metacast(_clname);
}

int ssvision::RoboticTCPServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ssvision::RoboticTCPServer::readData_signal(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ssvision::RoboticTCPServer::disConnect_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ssvision::RoboticTCPServer::newConnectIPportInfo_signal(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
