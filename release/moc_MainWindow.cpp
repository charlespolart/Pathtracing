/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[498];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 32), // "on_load3DFile_pushButton_clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 28), // "on_render_pushButton_clicked"
QT_MOC_LITERAL(4, 74, 26), // "on_stop_pushButton_clicked"
QT_MOC_LITERAL(5, 101, 32), // "on_width_spinBox_editingFinished"
QT_MOC_LITERAL(6, 134, 33), // "on_height_spinBox_editingFini..."
QT_MOC_LITERAL(7, 168, 45), // "on_cameraPositionX_doubleSpin..."
QT_MOC_LITERAL(8, 214, 5), // "value"
QT_MOC_LITERAL(9, 220, 45), // "on_cameraPositionY_doubleSpin..."
QT_MOC_LITERAL(10, 266, 45), // "on_cameraPositionZ_doubleSpin..."
QT_MOC_LITERAL(11, 312, 45), // "on_cameraRotationX_doubleSpin..."
QT_MOC_LITERAL(12, 358, 45), // "on_cameraRotationY_doubleSpin..."
QT_MOC_LITERAL(13, 404, 45), // "on_cameraRotationZ_doubleSpin..."
QT_MOC_LITERAL(14, 450, 14), // "disableOptions"
QT_MOC_LITERAL(15, 465, 6), // "status"
QT_MOC_LITERAL(16, 472, 13), // "writeTerminal"
QT_MOC_LITERAL(17, 486, 3), // "str"
QT_MOC_LITERAL(18, 490, 7) // "replace"

    },
    "MainWindow\0on_load3DFile_pushButton_clicked\0"
    "\0on_render_pushButton_clicked\0"
    "on_stop_pushButton_clicked\0"
    "on_width_spinBox_editingFinished\0"
    "on_height_spinBox_editingFinished\0"
    "on_cameraPositionX_doubleSpinBox_valueChanged\0"
    "value\0on_cameraPositionY_doubleSpinBox_valueChanged\0"
    "on_cameraPositionZ_doubleSpinBox_valueChanged\0"
    "on_cameraRotationX_doubleSpinBox_valueChanged\0"
    "on_cameraRotationY_doubleSpinBox_valueChanged\0"
    "on_cameraRotationZ_doubleSpinBox_valueChanged\0"
    "disableOptions\0status\0writeTerminal\0"
    "str\0replace"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       9,    1,   92,    2, 0x08 /* Private */,
      10,    1,   95,    2, 0x08 /* Private */,
      11,    1,   98,    2, 0x08 /* Private */,
      12,    1,  101,    2, 0x08 /* Private */,
      13,    1,  104,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      14,    1,  107,    2, 0x00 /* Private */,
      16,    2,  110,    2, 0x00 /* Private */,
      16,    1,  115,    2, 0x20 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,    8,

 // methods: parameters
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   17,   18,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_load3DFile_pushButton_clicked(); break;
        case 1: _t->on_render_pushButton_clicked(); break;
        case 2: _t->on_stop_pushButton_clicked(); break;
        case 3: _t->on_width_spinBox_editingFinished(); break;
        case 4: _t->on_height_spinBox_editingFinished(); break;
        case 5: _t->on_cameraPositionX_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->on_cameraPositionY_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_cameraPositionZ_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_cameraRotationX_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->on_cameraRotationY_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_cameraRotationZ_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->disableOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->writeTerminal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->writeTerminal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
