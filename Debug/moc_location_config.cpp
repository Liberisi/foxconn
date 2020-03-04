/****************************************************************************
** Meta object code from reading C++ file 'location_config.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../location_config.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'location_config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LocationConfigDialog_t {
    QByteArrayData data[15];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LocationConfigDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LocationConfigDialog_t qt_meta_stringdata_LocationConfigDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "LocationConfigDialog"
QT_MOC_LITERAL(1, 21, 24), // "on_camera_buffer_changed"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 7), // "Camera*"
QT_MOC_LITERAL(4, 55, 6), // "camera"
QT_MOC_LITERAL(5, 62, 18), // "on_robotic_command"
QT_MOC_LITERAL(6, 81, 17), // "RoboticTCPServer*"
QT_MOC_LITERAL(7, 99, 18), // "robotic_tcp_server"
QT_MOC_LITERAL(8, 118, 7), // "command"
QT_MOC_LITERAL(9, 126, 34), // "on_toolButton_choose_image_cl..."
QT_MOC_LITERAL(10, 161, 29), // "on_toolButton_extract_clicked"
QT_MOC_LITERAL(11, 191, 32), // "on_pushButton_save_image_clicked"
QT_MOC_LITERAL(12, 224, 40), // "on_toolButton_save_product_pa..."
QT_MOC_LITERAL(13, 265, 21), // "on_toolButton_clicked"
QT_MOC_LITERAL(14, 287, 39) // "on_pushButton_save_result_ima..."

    },
    "LocationConfigDialog\0on_camera_buffer_changed\0"
    "\0Camera*\0camera\0on_robotic_command\0"
    "RoboticTCPServer*\0robotic_tcp_server\0"
    "command\0on_toolButton_choose_image_clicked\0"
    "on_toolButton_extract_clicked\0"
    "on_pushButton_save_image_clicked\0"
    "on_toolButton_save_product_param_clicked\0"
    "on_toolButton_clicked\0"
    "on_pushButton_save_result_image_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LocationConfigDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       5,    2,   57,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,
      13,    0,   66,    2, 0x08 /* Private */,
      14,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LocationConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LocationConfigDialog *_t = static_cast<LocationConfigDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_camera_buffer_changed((*reinterpret_cast< Camera*(*)>(_a[1]))); break;
        case 1: _t->on_robotic_command((*reinterpret_cast< RoboticTCPServer*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->on_toolButton_choose_image_clicked(); break;
        case 3: _t->on_toolButton_extract_clicked(); break;
        case 4: _t->on_pushButton_save_image_clicked(); break;
        case 5: _t->on_toolButton_save_product_param_clicked(); break;
        case 6: _t->on_toolButton_clicked(); break;
        case 7: _t->on_pushButton_save_result_image_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject LocationConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LocationConfigDialog.data,
      qt_meta_data_LocationConfigDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LocationConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LocationConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LocationConfigDialog.stringdata0))
        return static_cast<void*>(const_cast< LocationConfigDialog*>(this));
    if (!strcmp(_clname, "HalconWidgetDelegate"))
        return static_cast< HalconWidgetDelegate*>(const_cast< LocationConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LocationConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
