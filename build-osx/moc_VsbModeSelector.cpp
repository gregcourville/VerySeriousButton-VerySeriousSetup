/****************************************************************************
** Meta object code from reading C++ file 'VsbModeSelector.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VsbModeSelector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VsbModeSelector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VsbModeButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_VsbModeButton[] = {
    "VsbModeButton\0"
};

void VsbModeButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData VsbModeButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VsbModeButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_VsbModeButton,
      qt_meta_data_VsbModeButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VsbModeButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VsbModeButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VsbModeButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VsbModeButton))
        return static_cast<void*>(const_cast< VsbModeButton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int VsbModeButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_VsbModeSelector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   17,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VsbModeSelector[] = {
    "VsbModeSelector\0\0x\0newSelectedMode(int)\0"
    "handleButtonPressed(int)\0"
};

void VsbModeSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VsbModeSelector *_t = static_cast<VsbModeSelector *>(_o);
        switch (_id) {
        case 0: _t->newSelectedMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->handleButtonPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VsbModeSelector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VsbModeSelector::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_VsbModeSelector,
      qt_meta_data_VsbModeSelector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VsbModeSelector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VsbModeSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VsbModeSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VsbModeSelector))
        return static_cast<void*>(const_cast< VsbModeSelector*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int VsbModeSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VsbModeSelector::newSelectedMode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
