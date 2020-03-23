/****************************************************************************
** Meta object code from reading C++ file 'SettingsWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SettingsWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingsWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingsWindow_t {
    QByteArrayData data[11];
    char stringdata0[365];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsWindow_t qt_meta_stringdata_SettingsWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SettingsWindow"
QT_MOC_LITERAL(1, 15, 32), // "on_width_spinBox_editingFinished"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 33), // "on_height_spinBox_editingFini..."
QT_MOC_LITERAL(4, 83, 45), // "on_cameraPositionX_doubleSpin..."
QT_MOC_LITERAL(5, 129, 5), // "value"
QT_MOC_LITERAL(6, 135, 45), // "on_cameraPositionY_doubleSpin..."
QT_MOC_LITERAL(7, 181, 45), // "on_cameraPositionZ_doubleSpin..."
QT_MOC_LITERAL(8, 227, 45), // "on_cameraRotationX_doubleSpin..."
QT_MOC_LITERAL(9, 273, 45), // "on_cameraRotationY_doubleSpin..."
QT_MOC_LITERAL(10, 319, 45) // "on_cameraRotationZ_doubleSpin..."

    },
    "SettingsWindow\0on_width_spinBox_editingFinished\0"
    "\0on_height_spinBox_editingFinished\0"
    "on_cameraPositionX_doubleSpinBox_valueChanged\0"
    "value\0on_cameraPositionY_doubleSpinBox_valueChanged\0"
    "on_cameraPositionZ_doubleSpinBox_valueChanged\0"
    "on_cameraRotationX_doubleSpinBox_valueChanged\0"
    "on_cameraRotationY_doubleSpinBox_valueChanged\0"
    "on_cameraRotationZ_doubleSpinBox_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,
       9,    1,   68,    2, 0x08 /* Private */,
      10,    1,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,

       0        // eod
};

void SettingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_width_spinBox_editingFinished(); break;
        case 1: _t->on_height_spinBox_editingFinished(); break;
        case 2: _t->on_cameraPositionX_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_cameraPositionY_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_cameraPositionZ_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->on_cameraRotationX_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->on_cameraRotationY_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_cameraRotationZ_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingsWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SettingsWindow.data,
    qt_meta_data_SettingsWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
