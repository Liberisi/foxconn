/****************************************************************************
** Meta object code from reading C++ file 'baojitai.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../baojitai.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baojitai.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Baojitai_t {
    QByteArrayData data[67];
    char stringdata0[1447];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Baojitai_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Baojitai_t qt_meta_stringdata_Baojitai = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Baojitai"
QT_MOC_LITERAL(1, 9, 15), // "signal_send_tid"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "SerialPort*"
QT_MOC_LITERAL(4, 38, 2), // "sp"
QT_MOC_LITERAL(5, 41, 15), // "signal_send_fid"
QT_MOC_LITERAL(6, 57, 26), // "signal_repair_mode_send_sn"
QT_MOC_LITERAL(7, 84, 30), // "signal_check_fid_board_leaving"
QT_MOC_LITERAL(8, 115, 31), // "signal_check_plc_camera_control"
QT_MOC_LITERAL(9, 147, 34), // "signal_post_process_location_..."
QT_MOC_LITERAL(10, 182, 38), // "signal_post_process_reading_c..."
QT_MOC_LITERAL(11, 221, 37), // "signal_post_process_check_fra..."
QT_MOC_LITERAL(12, 259, 12), // "signal_reset"
QT_MOC_LITERAL(13, 272, 27), // "signal_camera_status_change"
QT_MOC_LITERAL(14, 300, 7), // "Camera*"
QT_MOC_LITERAL(15, 308, 6), // "camera"
QT_MOC_LITERAL(16, 315, 28), // "signal_camera_buffer_updated"
QT_MOC_LITERAL(17, 344, 22), // "signal_location_finish"
QT_MOC_LITERAL(18, 367, 26), // "signal_reading_code_finish"
QT_MOC_LITERAL(19, 394, 25), // "signal_check_frame_finish"
QT_MOC_LITERAL(20, 420, 32), // "signal_serial_port_status_change"
QT_MOC_LITERAL(21, 453, 11), // "serial_port"
QT_MOC_LITERAL(22, 465, 23), // "signal_serial_port_read"
QT_MOC_LITERAL(23, 489, 7), // "message"
QT_MOC_LITERAL(24, 497, 21), // "signal_product_change"
QT_MOC_LITERAL(25, 519, 8), // "Product*"
QT_MOC_LITERAL(26, 528, 7), // "product"
QT_MOC_LITERAL(27, 536, 28), // "signal_robotic_status_change"
QT_MOC_LITERAL(28, 565, 17), // "RoboticTCPServer*"
QT_MOC_LITERAL(29, 583, 18), // "robotic_tcp_server"
QT_MOC_LITERAL(30, 602, 22), // "signal_robotic_command"
QT_MOC_LITERAL(31, 625, 7), // "command"
QT_MOC_LITERAL(32, 633, 24), // "signal_plc_status_change"
QT_MOC_LITERAL(33, 658, 29), // "signal_plc_repair_mode_change"
QT_MOC_LITERAL(34, 688, 16), // "signal_plc_reset"
QT_MOC_LITERAL(35, 705, 28), // "signal_running_status_change"
QT_MOC_LITERAL(36, 734, 35), // "signal_advanced_device_count_..."
QT_MOC_LITERAL(37, 770, 35), // "signal_fid_cmc_socket_status_..."
QT_MOC_LITERAL(38, 806, 21), // "signal_product_arrive"
QT_MOC_LITERAL(39, 828, 19), // "signal_product_info"
QT_MOC_LITERAL(40, 848, 4), // "info"
QT_MOC_LITERAL(41, 853, 18), // "signal_location_ng"
QT_MOC_LITERAL(42, 872, 13), // "signal_tid_ng"
QT_MOC_LITERAL(43, 886, 3), // "tid"
QT_MOC_LITERAL(44, 890, 6), // "reason"
QT_MOC_LITERAL(45, 897, 12), // "signal_sn_ng"
QT_MOC_LITERAL(46, 910, 2), // "sn"
QT_MOC_LITERAL(47, 913, 13), // "signal_fid_ng"
QT_MOC_LITERAL(48, 927, 3), // "fid"
QT_MOC_LITERAL(49, 931, 33), // "on_signal_check_fid_board_lea..."
QT_MOC_LITERAL(50, 965, 34), // "on_signal_check_plc_camera_co..."
QT_MOC_LITERAL(51, 1000, 18), // "on_signal_send_tid"
QT_MOC_LITERAL(52, 1019, 18), // "on_signal_send_fid"
QT_MOC_LITERAL(53, 1038, 29), // "on_signal_repair_mode_send_sn"
QT_MOC_LITERAL(54, 1068, 37), // "on_signal_post_process_locati..."
QT_MOC_LITERAL(55, 1106, 41), // "on_signal_post_process_readin..."
QT_MOC_LITERAL(56, 1148, 40), // "on_signal_post_process_check_..."
QT_MOC_LITERAL(57, 1189, 15), // "on_signal_reset"
QT_MOC_LITERAL(58, 1205, 32), // "on_timer_check_fid_board_leaving"
QT_MOC_LITERAL(59, 1238, 33), // "on_timer_check_plc_camera_con..."
QT_MOC_LITERAL(60, 1272, 23), // "on_timer_try_sending_sn"
QT_MOC_LITERAL(61, 1296, 26), // "on_timer_send_undo_postfix"
QT_MOC_LITERAL(62, 1323, 25), // "on_timer_check_tid_result"
QT_MOC_LITERAL(63, 1349, 24), // "on_timer_check_sn_result"
QT_MOC_LITERAL(64, 1374, 22), // "on_waiting_fid_timeout"
QT_MOC_LITERAL(65, 1397, 25), // "on_timer_check_fid_result"
QT_MOC_LITERAL(66, 1423, 23) // "on_receive_fid_ok_or_ng"

    },
    "Baojitai\0signal_send_tid\0\0SerialPort*\0"
    "sp\0signal_send_fid\0signal_repair_mode_send_sn\0"
    "signal_check_fid_board_leaving\0"
    "signal_check_plc_camera_control\0"
    "signal_post_process_location_image\0"
    "signal_post_process_reading_code_image\0"
    "signal_post_process_check_frame_image\0"
    "signal_reset\0signal_camera_status_change\0"
    "Camera*\0camera\0signal_camera_buffer_updated\0"
    "signal_location_finish\0"
    "signal_reading_code_finish\0"
    "signal_check_frame_finish\0"
    "signal_serial_port_status_change\0"
    "serial_port\0signal_serial_port_read\0"
    "message\0signal_product_change\0Product*\0"
    "product\0signal_robotic_status_change\0"
    "RoboticTCPServer*\0robotic_tcp_server\0"
    "signal_robotic_command\0command\0"
    "signal_plc_status_change\0"
    "signal_plc_repair_mode_change\0"
    "signal_plc_reset\0signal_running_status_change\0"
    "signal_advanced_device_count_change\0"
    "signal_fid_cmc_socket_status_change\0"
    "signal_product_arrive\0signal_product_info\0"
    "info\0signal_location_ng\0signal_tid_ng\0"
    "tid\0reason\0signal_sn_ng\0sn\0signal_fid_ng\0"
    "fid\0on_signal_check_fid_board_leaving\0"
    "on_signal_check_plc_camera_control\0"
    "on_signal_send_tid\0on_signal_send_fid\0"
    "on_signal_repair_mode_send_sn\0"
    "on_signal_post_process_location_image\0"
    "on_signal_post_process_reading_code_image\0"
    "on_signal_post_process_check_frame_image\0"
    "on_signal_reset\0on_timer_check_fid_board_leaving\0"
    "on_timer_check_plc_camera_control\0"
    "on_timer_try_sending_sn\0"
    "on_timer_send_undo_postfix\0"
    "on_timer_check_tid_result\0"
    "on_timer_check_sn_result\0"
    "on_waiting_fid_timeout\0on_timer_check_fid_result\0"
    "on_receive_fid_ok_or_ng"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Baojitai[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      31,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  259,    2, 0x06 /* Public */,
       5,    1,  262,    2, 0x06 /* Public */,
       6,    0,  265,    2, 0x06 /* Public */,
       7,    0,  266,    2, 0x06 /* Public */,
       8,    0,  267,    2, 0x06 /* Public */,
       9,    0,  268,    2, 0x06 /* Public */,
      10,    0,  269,    2, 0x06 /* Public */,
      11,    0,  270,    2, 0x06 /* Public */,
      12,    0,  271,    2, 0x06 /* Public */,
      13,    1,  272,    2, 0x06 /* Public */,
      16,    1,  275,    2, 0x06 /* Public */,
      17,    0,  278,    2, 0x06 /* Public */,
      18,    0,  279,    2, 0x06 /* Public */,
      19,    0,  280,    2, 0x06 /* Public */,
      20,    1,  281,    2, 0x06 /* Public */,
      22,    2,  284,    2, 0x06 /* Public */,
      24,    1,  289,    2, 0x06 /* Public */,
      27,    1,  292,    2, 0x06 /* Public */,
      30,    2,  295,    2, 0x06 /* Public */,
      32,    0,  300,    2, 0x06 /* Public */,
      33,    0,  301,    2, 0x06 /* Public */,
      34,    0,  302,    2, 0x06 /* Public */,
      35,    0,  303,    2, 0x06 /* Public */,
      36,    0,  304,    2, 0x06 /* Public */,
      37,    0,  305,    2, 0x06 /* Public */,
      38,    0,  306,    2, 0x06 /* Public */,
      39,    1,  307,    2, 0x06 /* Public */,
      41,    0,  310,    2, 0x06 /* Public */,
      42,    2,  311,    2, 0x06 /* Public */,
      45,    3,  316,    2, 0x06 /* Public */,
      47,    2,  323,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      49,    0,  328,    2, 0x08 /* Private */,
      50,    0,  329,    2, 0x08 /* Private */,
      51,    1,  330,    2, 0x08 /* Private */,
      52,    1,  333,    2, 0x08 /* Private */,
      53,    0,  336,    2, 0x08 /* Private */,
      54,    0,  337,    2, 0x08 /* Private */,
      55,    0,  338,    2, 0x08 /* Private */,
      56,    0,  339,    2, 0x08 /* Private */,
      57,    0,  340,    2, 0x08 /* Private */,
      58,    0,  341,    2, 0x08 /* Private */,
      59,    0,  342,    2, 0x08 /* Private */,
      60,    0,  343,    2, 0x08 /* Private */,
      61,    0,  344,    2, 0x08 /* Private */,
      62,    0,  345,    2, 0x08 /* Private */,
      63,    0,  346,    2, 0x08 /* Private */,
      64,    0,  347,    2, 0x08 /* Private */,
      65,    0,  348,    2, 0x08 /* Private */,
      66,    0,  349,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   21,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,   21,   23,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 28, QMetaType::QString,   29,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   43,   44,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   46,   44,   43,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   48,   44,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Baojitai::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Baojitai *_t = static_cast<Baojitai *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_send_tid((*reinterpret_cast< SerialPort*(*)>(_a[1]))); break;
        case 1: _t->signal_send_fid((*reinterpret_cast< SerialPort*(*)>(_a[1]))); break;
        case 2: _t->signal_repair_mode_send_sn(); break;
        case 3: _t->signal_check_fid_board_leaving(); break;
        case 4: _t->signal_check_plc_camera_control(); break;
        case 5: _t->signal_post_process_location_image(); break;
        case 6: _t->signal_post_process_reading_code_image(); break;
        case 7: _t->signal_post_process_check_frame_image(); break;
        case 8: _t->signal_reset(); break;
        case 9: _t->signal_camera_status_change((*reinterpret_cast< Camera*(*)>(_a[1]))); break;
        case 10: _t->signal_camera_buffer_updated((*reinterpret_cast< Camera*(*)>(_a[1]))); break;
        case 11: _t->signal_location_finish(); break;
        case 12: _t->signal_reading_code_finish(); break;
        case 13: _t->signal_check_frame_finish(); break;
        case 14: _t->signal_serial_port_status_change((*reinterpret_cast< SerialPort*(*)>(_a[1]))); break;
        case 15: _t->signal_serial_port_read((*reinterpret_cast< SerialPort*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->signal_product_change((*reinterpret_cast< Product*(*)>(_a[1]))); break;
        case 17: _t->signal_robotic_status_change((*reinterpret_cast< RoboticTCPServer*(*)>(_a[1]))); break;
        case 18: _t->signal_robotic_command((*reinterpret_cast< RoboticTCPServer*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: _t->signal_plc_status_change(); break;
        case 20: _t->signal_plc_repair_mode_change(); break;
        case 21: _t->signal_plc_reset(); break;
        case 22: _t->signal_running_status_change(); break;
        case 23: _t->signal_advanced_device_count_change(); break;
        case 24: _t->signal_fid_cmc_socket_status_change(); break;
        case 25: _t->signal_product_arrive(); break;
        case 26: _t->signal_product_info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->signal_location_ng(); break;
        case 28: _t->signal_tid_ng((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: _t->signal_sn_ng((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 30: _t->signal_fid_ng((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 31: _t->on_signal_check_fid_board_leaving(); break;
        case 32: _t->on_signal_check_plc_camera_control(); break;
        case 33: _t->on_signal_send_tid((*reinterpret_cast< SerialPort*(*)>(_a[1]))); break;
        case 34: _t->on_signal_send_fid((*reinterpret_cast< SerialPort*(*)>(_a[1]))); break;
        case 35: _t->on_signal_repair_mode_send_sn(); break;
        case 36: _t->on_signal_post_process_location_image(); break;
        case 37: _t->on_signal_post_process_reading_code_image(); break;
        case 38: _t->on_signal_post_process_check_frame_image(); break;
        case 39: _t->on_signal_reset(); break;
        case 40: _t->on_timer_check_fid_board_leaving(); break;
        case 41: _t->on_timer_check_plc_camera_control(); break;
        case 42: _t->on_timer_try_sending_sn(); break;
        case 43: _t->on_timer_send_undo_postfix(); break;
        case 44: _t->on_timer_check_tid_result(); break;
        case 45: _t->on_timer_check_sn_result(); break;
        case 46: _t->on_waiting_fid_timeout(); break;
        case 47: _t->on_timer_check_fid_result(); break;
        case 48: _t->on_receive_fid_ok_or_ng(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Baojitai::*_t)(SerialPort * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_send_tid)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(SerialPort * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_send_fid)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_repair_mode_send_sn)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_check_fid_board_leaving)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_check_plc_camera_control)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_post_process_location_image)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_post_process_reading_code_image)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_post_process_check_frame_image)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_reset)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(Camera * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_camera_status_change)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(Camera * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_camera_buffer_updated)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_location_finish)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_reading_code_finish)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_check_frame_finish)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(SerialPort * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_serial_port_status_change)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(SerialPort * , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_serial_port_read)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(Product * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_product_change)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(RoboticTCPServer * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_robotic_status_change)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(RoboticTCPServer * , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_robotic_command)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_plc_status_change)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_plc_repair_mode_change)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_plc_reset)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_running_status_change)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_advanced_device_count_change)) {
                *result = 23;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_fid_cmc_socket_status_change)) {
                *result = 24;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_product_arrive)) {
                *result = 25;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_product_info)) {
                *result = 26;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_location_ng)) {
                *result = 27;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_tid_ng)) {
                *result = 28;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_sn_ng)) {
                *result = 29;
                return;
            }
        }
        {
            typedef void (Baojitai::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Baojitai::signal_fid_ng)) {
                *result = 30;
                return;
            }
        }
    }
}

const QMetaObject Baojitai::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Baojitai.data,
      qt_meta_data_Baojitai,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Baojitai::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Baojitai::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Baojitai.stringdata0))
        return static_cast<void*>(const_cast< Baojitai*>(this));
    if (!strcmp(_clname, "SerialPortDelegate"))
        return static_cast< SerialPortDelegate*>(const_cast< Baojitai*>(this));
    if (!strcmp(_clname, "RoboticTCPServerDelegate"))
        return static_cast< RoboticTCPServerDelegate*>(const_cast< Baojitai*>(this));
    if (!strcmp(_clname, "CameraDelegate"))
        return static_cast< CameraDelegate*>(const_cast< Baojitai*>(this));
    if (!strcmp(_clname, "ItemInformationCenterDelegate"))
        return static_cast< ItemInformationCenterDelegate*>(const_cast< Baojitai*>(this));
    if (!strcmp(_clname, "FidCMCSocketDelegate"))
        return static_cast< FidCMCSocketDelegate*>(const_cast< Baojitai*>(this));
    return QObject::qt_metacast(_clname);
}

int Baojitai::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 49;
    }
    return _id;
}

// SIGNAL 0
void Baojitai::signal_send_tid(SerialPort * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Baojitai::signal_send_fid(SerialPort * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Baojitai::signal_repair_mode_send_sn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Baojitai::signal_check_fid_board_leaving()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Baojitai::signal_check_plc_camera_control()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Baojitai::signal_post_process_location_image()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void Baojitai::signal_post_process_reading_code_image()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void Baojitai::signal_post_process_check_frame_image()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void Baojitai::signal_reset()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void Baojitai::signal_camera_status_change(Camera * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Baojitai::signal_camera_buffer_updated(Camera * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Baojitai::signal_location_finish()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void Baojitai::signal_reading_code_finish()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void Baojitai::signal_check_frame_finish()
{
    QMetaObject::activate(this, &staticMetaObject, 13, Q_NULLPTR);
}

// SIGNAL 14
void Baojitai::signal_serial_port_status_change(SerialPort * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Baojitai::signal_serial_port_read(SerialPort * _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void Baojitai::signal_product_change(Product * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void Baojitai::signal_robotic_status_change(RoboticTCPServer * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void Baojitai::signal_robotic_command(RoboticTCPServer * _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void Baojitai::signal_plc_status_change()
{
    QMetaObject::activate(this, &staticMetaObject, 19, Q_NULLPTR);
}

// SIGNAL 20
void Baojitai::signal_plc_repair_mode_change()
{
    QMetaObject::activate(this, &staticMetaObject, 20, Q_NULLPTR);
}

// SIGNAL 21
void Baojitai::signal_plc_reset()
{
    QMetaObject::activate(this, &staticMetaObject, 21, Q_NULLPTR);
}

// SIGNAL 22
void Baojitai::signal_running_status_change()
{
    QMetaObject::activate(this, &staticMetaObject, 22, Q_NULLPTR);
}

// SIGNAL 23
void Baojitai::signal_advanced_device_count_change()
{
    QMetaObject::activate(this, &staticMetaObject, 23, Q_NULLPTR);
}

// SIGNAL 24
void Baojitai::signal_fid_cmc_socket_status_change()
{
    QMetaObject::activate(this, &staticMetaObject, 24, Q_NULLPTR);
}

// SIGNAL 25
void Baojitai::signal_product_arrive()
{
    QMetaObject::activate(this, &staticMetaObject, 25, Q_NULLPTR);
}

// SIGNAL 26
void Baojitai::signal_product_info(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void Baojitai::signal_location_ng()
{
    QMetaObject::activate(this, &staticMetaObject, 27, Q_NULLPTR);
}

// SIGNAL 28
void Baojitai::signal_tid_ng(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void Baojitai::signal_sn_ng(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void Baojitai::signal_fid_ng(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}
QT_END_MOC_NAMESPACE
