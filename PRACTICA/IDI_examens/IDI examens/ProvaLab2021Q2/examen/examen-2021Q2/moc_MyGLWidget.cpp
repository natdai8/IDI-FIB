/****************************************************************************
** Meta object code from reading C++ file 'MyGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MyGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGLWidget_t {
    QByteArrayData data[8];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGLWidget_t qt_meta_stringdata_MyGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MyGLWidget"
QT_MOC_LITERAL(1, 11, 7), // "camPers"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "camOrto"
QT_MOC_LITERAL(4, 28, 11), // "girPatricio"
QT_MOC_LITERAL(5, 40, 12), // "canviCamaraP"
QT_MOC_LITERAL(6, 53, 12), // "canviCamaraO"
QT_MOC_LITERAL(7, 66, 4) // "girP"

    },
    "MyGLWidget\0camPers\0\0camOrto\0girPatricio\0"
    "canviCamaraP\0canviCamaraO\0girP"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->camPers(); break;
        case 1: _t->camOrto(); break;
        case 2: _t->girPatricio(); break;
        case 3: _t->canviCamaraP(); break;
        case 4: _t->canviCamaraO(); break;
        case 5: _t->girP(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::camPers)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::camOrto)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::girPatricio)) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MyGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<ExamGLWidget::staticMetaObject>(),
    qt_meta_stringdata_MyGLWidget.data,
    qt_meta_data_MyGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGLWidget.stringdata0))
        return static_cast<void*>(this);
    return ExamGLWidget::qt_metacast(_clname);
}

int MyGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ExamGLWidget::qt_metacall(_c, _id, _a);
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
void MyGLWidget::camPers()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyGLWidget::camOrto()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyGLWidget::girPatricio()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
