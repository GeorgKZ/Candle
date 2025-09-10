#include <string>

#include <QAbstractButton>
#include <QAbstractItemDelegate>
#include <QAbstractItemView>
#include <QBoxLayout>
#include <QColor>
#include <QComboBox>
#include <QDir>
#include <QFile>
#include <QHeaderView>
#include <QIcon>
#include <QIODevice>
#include <QLayout>
#include <QLayoutItem>
#include <QObject>
#include <QSettings>
#include <QSize>
#include <QSizePolicy>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QUiLoader>
#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "wrapper_common.h"
#include "wrapper_Slider.h"
#include "wrapper_SliderBox.h"
#include "wrapper_StyledToolButton.h"
#include "wrapper_CameraWidget.h"
#include "wrapper_ColorPicker.h"
#include "wrapper_Delegate.h"

#include "wrapper_QAction.h"
#include "wrapper_QAbstractButton.h"
#include "wrapper_QAbstractItemDelegate.h"
#include "wrapper_QAbstractItemView.h"
#include "wrapper_QBoxLayout.h"
#include "wrapper_QColor.h"
#include "wrapper_QComboBox.h"
#include "wrapper_QDir.h"
#include "wrapper_QGridLayout.h"
#include "wrapper_QFile.h"
#include "wrapper_QHeaderView.h"
#include "wrapper_QIcon.h"
#include "wrapper_QIODevice.h"
#include "wrapper_QLayout.h"
#include "wrapper_QLayoutItem.h"
#include "wrapper_QLineEdit.h"
#include "wrapper_QModelIndex.h"
#include "wrapper_QObject.h"
#include "wrapper_QPainter.h"
#include "wrapper_QPoint.h"
#include "wrapper_QPointF.h"
#include "wrapper_QPushButton.h"
#include "wrapper_QRect.h"
#include "wrapper_QRectF.h"
#include "wrapper_QSettings.h"
#include "wrapper_QSize.h"
#include "wrapper_QSizePolicy.h"
#include "wrapper_QSpinBox.h"
#include "wrapper_QStyledItemDelegate.h"
#include "wrapper_QTableView.h"
#include "wrapper_QTableWidget.h"
#include "wrapper_QTableWidgetItem.h"
#include "wrapper_QToolButton.h"
#include "wrapper_QUiLoader.h"
#include "wrapper_QWidget.h"

/**
 * \file
 * * \copybrief variantToJSValue(const QVariant&, QJSEngine*)
 */
QJSValue variantToJSValue(const QVariant &variant, QJSEngine *engine) {
  QJSValue retval;

  if (variant.isNull()) {
    qWarning() << "variantToJSValue - null var. Return empty QJSValue";
    return retval;
  }

  if (!variant.isValid()) {
    qWarning() << "variantToJSValue - invalid var. Return empty QJSValue";
    return retval;
  }

  const char* typeName = variant.typeName();
  if (typeName == nullptr) {
    qWarning() << "variantToJSValue - no type. Return empty QJSValue";
    return retval;
  }

  qDebug() << "variantToJSValue - type is" << typeName;
  std::string typeString(typeName);

  if (typeString.compare("QString") == 0) {
    qDebug() << "variantToJSValue - string value is" << variant.toString();
    return QJSValue(variant.toString());
  } else if (typeString.compare("int") == 0) {
    qDebug() << "variantToJSValue - int value is" << variant.toInt();
    return QJSValue(variant.toInt());
  } else if (typeString.compare("QVariantList") == 0) {
    QVariantList varlist = variant.toList();
    QJSValueList jslist;
    for (qsizetype i = 0; i < varlist.size(); ++i) {
      jslist += variantToJSValue(varlist[i], engine);
    }
    return engine->toScriptValue<QJSValueList>(jslist);
  } else if (typeString.compare("QIcon") == 0) {
  qDebug() << "variantToJSValue - wrapping QIcon";
    const QIcon &icon = qvariant_cast<QIcon>(variant);
    wrapper_QIcon *wrapped_object = new wrapper_QIcon(new QIcon(icon));
    return engine->toScriptValue<wrapper_QIcon*>(wrapped_object);
  }

  qDebug() << "ERROR: variantToJSValue - unknown unwrapped type";
  return engine->toScriptValue<QVariant>(variant);
}

/**
 * \file
 * * \copybrief jsvalueToVariant(const QJSValue&)
 */
QVariant jsvalueToVariant(const QJSValue &value)
{

#if 0
bool 	isArray() const
bool 	isBool() const
bool 	isCallable() const
bool 	isDate() const
bool 	isError() const
bool 	isNull() const
bool 	isNumber() const
bool 	isObject() const
bool 	isQMetaObject() const
bool 	isQObject() const
bool 	isRegExp() const
bool 	isString() const
bool 	isUndefined() const
bool 	isUrl() const
#endif

  QString typeString; // Тип объекта, хранящегося в QJSValue 
  void *ptr = jsvalueToObject_ptr(nullptr, value, &typeString);
  if (ptr == nullptr) {
    qWarning() << "jsvalueToVariant - can't get object ptr; returning empty QVariant";
    return QVariant();
  }
  qDebug() << "jsvalueToVariant - got" << typeString << "type";

  if (typeString == "QIcon") {
      qDebug() << "jsvalueToVariant - returning QIcon";
      return QVariant(*static_cast<QIcon*>(ptr));
  }
  if (typeString == "qint32") {
      qDebug() << "jsvalueToVariant - returning qint32";
      return QVariant(*static_cast<qint32*>(ptr));
  }
  if (typeString == "QString") {
      qDebug() << "jsvalueToVariant - returning QString";
      return QVariant(*static_cast<QString*>(ptr));
  }
  if (typeString == "QVariantList") {
      qDebug() << "jsvalueToVariant - returning QVariantList";
      return QVariant(*static_cast<QVariantList*>(ptr));
  }

//!!!TODO!!! А также прочие типы, которые могут храниться в QJSValue

#if 0
  if (typeString == "QVariantList") {
    QVariantList oldvarlist = variant.toList();
    QVariantList newvarlist;
    for (qsizetype i = 0; i < oldvarlist.size(); ++i) {
      QVariant oldvar = oldvarlist[i];
      QVariant newvar = oldvar;
      newvarlist += newvar;
    }
    return newvarlist;
  }
#endif


#if 0
  // Проверить, вдруг в JSValue находится Variant с объектом или прокси-объектом
  QVariant variant = value.toVariant();
  if (variant.isValid() && !variant.isNull() && value.toQObject() == nullptr) {
    qDebug() << "jsvalueToVariant - value is Variant; checking type...";
    const char* typeName = variant.typeName();
    if (typeName == nullptr) {
      qDebug() << "ERROR: jsvalueToVariant - no variant type. Returning empty QVariant";
      return QVariant();
    }
    qDebug() << "jsvalueToVariant - type is" << typeName;
    if (strcmp(typeName, "wrapper_QIcon") == 0) {
      QIcon *ptr = (qvariant_cast<wrapper_QIcon*>(variant))->get_selfptr();
      qDebug() << "jsvalueToVariant - returning QIcon";
      return *ptr; //!!!
    }
    if (strcmp(typeName, "QString") == 0) {
      qDebug() << "jsvalueToVariant - returning QString";
      return variant.toString();
    }
    if (strcmp(typeName, "int") == 0) {
      qDebug() << "jsvalueToVariant - returning qint32";
      return variant.toInt();
    }
    if (strcmp(typeName, "QVariantList") == 0) {
      QVariantList oldvarlist = variant.toList();
      QVariantList newvarlist;
      for (qsizetype i = 0; i < oldvarlist.size(); ++i) {
        QVariant oldvar = oldvarlist[i];
        QVariant newvar = oldvar;
        newvarlist += newvar;
      }
      return newvarlist;
    }

    qDebug() << "ERROR: jsvalueToVariant - unsupported type/wrapper. Returning value.toVariant()";
    return value.toVariant(QJSValue::RetainJSObjects);
  }

  QObject* obj = value.toQObject();
  if (obj == nullptr) {
    qCritical() << "jsvalueToVariant - value is not QObject. Returning value.toVariant()";
    return value.toVariant(QJSValue::RetainJSObjects);
  }
  const QMetaObject* mobj = obj->metaObject();
  if (mobj == nullptr) {
    qCritical() << "jsvalueToVariant - value is QObject but not QMetaObject. Returning value.toVariant()";
    return value.toVariant(QJSValue::RetainJSObjects);
  }
  const char* objName = mobj->className();
  if (objName == nullptr) {
    qCritical() << "jsvalueToVariant - value is QMetaObject but has no name. Returning value.toVariant()";
    return value.toVariant(QJSValue::RetainJSObjects);
  }
  std::string objNameString = objName;
  qDebug() << "jsvalueToVariant - type is" << objName;
  if (objNameString.compare("wrapper_QIcon") == 0) {
    QIcon* icon = (static_cast<wrapper_QIcon*>(obj))->get_selfptr();
    qDebug() << "jsvalueToVariant - returning QIcon:" << *icon;
    QVariant var = QIcon(*icon); 
    return var; 
  }

  qDebug() << "ERROR: jsvalueToVariant - unsupported type/wrapper. Returning value.toVariant()";
  return value.toVariant(QJSValue::RetainJSObjects);
#endif

    qWarning() << "jsvalueToVariant - unknown type, returning empty QVariant";
    return QVariant();
}

/**
 * \file
 * * \copybrief wrapper_common::wrapper_common(void*)
 */
wrapper_common::wrapper_common(void *self) : selfptr_(self) {
//  qDebug() << "wrapper_common::constructor(self=" << get_selfvalue() << ")";
}

/**
 * \file
 * * \copybrief wrapper_common::~wrapper_common()
 */
wrapper_common::~wrapper_common() {
    qDebug() << "wrapper_common::destructor";
}

/**
 * \file
 * * \copybrief wrapper_common::get_selfptr() const
 */
const void* wrapper_common::get_selfptr() const {
    if (selfptr_ == nullptr) {
        qCritical() << "const wrapper_common::get_selfptr - got nullptr";
    }
    return selfptr_;
}

/**
 * \file
 * * \copybrief wrapper_common::get_selfptr()
 */
void* wrapper_common::get_selfptr() {
    if (selfptr_ == nullptr) {
        qCritical() << "wrapper_common::get_selfptr - got nullptr";
    }
//  qDebug() << "wrapper_common::get_selfptr() ->" << get_selfvalue();
    return selfptr_;
}

/**
 * \file
 * * \copybrief wrapper_common::variantToJSValue(const QVariant&) const
 */
QJSValue wrapper_common::variantToJSValue(const QVariant &variant) const {
    qDebug() << "wrapper_common::variantToJSValue...";
    return ::variantToJSValue(variant, qjsEngine(this));
}

QJSValue wrapper_common::PointerToJsvalue(QObject *object) const
{
    const QMetaObject *mo = object->metaObject();
    if (mo != nullptr)
    {
        const char *class_name = mo->className();
        if (class_name != nullptr)
        {
            return PointerToJsvalue(class_name, object);
        }
    }
    qCritical() << "wrapper_common::PointerToJsvalue(QObject*) - no meta name!";
    return QJSValue();
}

#define wfactory(class, name, obj) do { if (strcmp(class, #name ) == 0) { \
  return PointerToJsvalueMacro(name, object); } } while(0)

QJSValue wrapper_common::PointerToJsvalue(const char *className, void *object) const
{
  wfactory(className, QAbstractButton, object);
  wfactory(className, QAbstractItemDelegate, object);
  wfactory(className, QAbstractItemView, object);
  wfactory(className, QAbstractSpinBox, object);
  wfactory(className, QBoxLayout, object);
  wfactory(className, QHBoxLayout, object);
  wfactory(className, QVBoxLayout, object);
  wfactory(className, QColor, object);
  wfactory(className, QComboBox, object);
  wfactory(className, QDir, object);
  wfactory(className, QDoubleSpinBox, object);
  wfactory(className, QGridLayout, object);
  wfactory(className, QFile, object);
  wfactory(className, QHeaderView, object);
  wfactory(className, QIcon, object);
  wfactory(className, QIODevice, object);
  wfactory(className, QLayout, object);
  wfactory(className, QLayoutItem, object);
  wfactory(className, QLineEdit, object);
  wfactory(className, QModelIndex, object);
  wfactory(className, QObject, object);
  wfactory(className, QPainter, object);
  wfactory(className, QPaintDevice, object);
  wfactory(className, QPoint, object);
  wfactory(className, QPointF, object);
  wfactory(className, QPushButton, object);
  wfactory(className, QRect, object);
  wfactory(className, QRectF, object);
  wfactory(className, QSettings, object);
  wfactory(className, QSize, object);
  wfactory(className, QSizePolicy, object);
  wfactory(className, QSlider, object);
  wfactory(className, QSpinBox, object);
  wfactory(className, QStyledItemDelegate, object);
  wfactory(className, QTableView, object);
  wfactory(className, QTableWidget, object);
  wfactory(className, QTableWidgetItem, object);
  wfactory(className, QToolButton, object);
  wfactory(className, QUiLoader, object);
  wfactory(className, QWidget, object);

  // Пользовательские виджеты
  wfactory(className, CameraWidget, object);
  wfactory(className, ColorPicker, object);
  wfactory(className, Slider, object);
  wfactory(className, SliderBox, object);
  wfactory(className, StyledToolButton, object);

  qCritical() << "PointerToJsvalue("  << className << ") - unknown class name";
  return PointerToJsvalueMacro(QObject, object);
}


unsigned long long wrapper_common::get_selfvalue() const {
    return reinterpret_cast<unsigned long long>(selfptr_);
}


// Регистрация прокси-класса
#define wregister(name) do { se->globalObject().setProperty( #name , se->newQMetaObject(&wrapper_##name::staticMetaObject) ); } while(0)

//#define wregister(name) do { se->globalObject().setProperty( #name , se->newQMetaObject<wrapper_##name>() ); } while(0)

/**
 * \file
 * * \copybrief register_wrappers(QJSEngine*)
 */
WRAPPER_DLL_EXPORT void register_wrappers(QJSEngine *se) {

  // Прокси-классы Qt
  wregister(QAbstractButton);
  wregister(QAbstractItemDelegate);
  wregister(QAbstractItemView);
  wregister(QAction);

  wregister(QBoxLayout);
  wregister(QVBoxLayout);
  wregister(QHBoxLayout);

  wregister(QColor);
  wregister(QComboBox);
  wregister(QDir);
  wregister(QDoubleSpinBox);
  wregister(QFile);
  wregister(QHeaderView);
  wregister(QIcon);
  wregister(QIODevice);

  wregister(QLayout);
  wregister(QGridLayout);

  wregister(QLayoutItem);
  wregister(QLineEdit);
  wregister(QModelIndex);
  wregister(QObject);
  wregister(QPainter);
  wregister(QPaintDevice);
  wregister(QPoint);
  wregister(QPointF);
  wregister(QPushButton);
  wregister(QRect);
  wregister(QRectF);
  wregister(QSettings);
  wregister(QSize);
  wregister(QSizePolicy);
  wregister(QSlider);
  wregister(QSpinBox);
  wregister(QStyledItemDelegate);
  wregister(QTableView);
  wregister(QTableWidget);
  wregister(QTableWidgetItem);
  wregister(QToolButton);
  wregister(QUiLoader);
  wregister(QWidget);

  // Прокси-классы пользовательских виджетов
    wregister(StyledToolButton);
//  wregister(CameraWidget);
//  wregister(ColorPicker);
//  wregister(Slider);
//  wregister(SliderBox);
//    wregister(IconDelegate);
//    wregister(CodeDelegate);

  qDebug() << "register_wrappers - OK";
}

/**
 * \file
 * * \copybrief jsvalueToObject_ptr(const char*, const QJSValue&, QString*)
 */
void *jsvalueToObject_ptr(const char *waiting_className, const QJSValue &value, QString *returnType) {

  if (value.isNull()) {
    qDebug() << "ERROR: jsvalueToObject_ptr(" <<  waiting_className << ") - value is Null. Returning nullptr";
    return nullptr;
  }

  if (value.isUndefined()) {
    qDebug() << "jsvalueToObject_ptr(" <<  waiting_className << ") - value is Undefined. Returning nullptr";
    return nullptr;
  }

  // Проверить, вдруг в JSValue находится Variant с простым или прокси-типом
  QVariant variant = value.toVariant();
  if (variant.isValid() && !variant.isNull() && value.toQObject() == nullptr) {
    const char* typeName = variant.typeName();
    if (typeName == nullptr) {
      qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - Variant without type. Returning nullptr";
      return nullptr;
    }

    if (strcmp(typeName, "QString") == 0) {
      qDebug() << "jsvalueToObject_ptr(" <<  waiting_className << ") - returning QString pointer";
      if (returnType != nullptr) *returnType = "QString";
      return new QString(variant.toString());
    }
    if (strcmp(typeName, "int") == 0) {
      qDebug() << "jsvalueToObject_ptr(" <<  waiting_className << ") - returning qint32 pointer";
      if (returnType != nullptr) *returnType = "qint32";
      return new qint32(variant.toInt());
    }

    //!!!TODO!!! И другие типы данных, которые могут храниться в QVariant...

    if (strcmp(typeName, "QVariantList") == 0) {
      QVariantList oldvarlist = variant.toList();
      QVariantList *newvarlist = new QVariantList;
      for (qsizetype i = 0; i < oldvarlist.size(); ++i) {
        QVariant oldvar = oldvarlist[i];
        QVariant newvar = oldvar;
        *newvarlist += newvar;
      }
      qDebug() << "jsvalueToObject_ptr(" <<  waiting_className << ") - returning QVariantList pointer";
      if (returnType != nullptr) *returnType = "QVariantList";
      return newvarlist;
    }


    bool isWrapper = false;
    QString wrapperName = typeName;
    QString wrappedName;
    if (wrapperName.size() > 8) {
        wrapperName.truncate(8);
        if (QString("wrapper_") == wrapperName) {
            isWrapper = true;
            wrappedName = QString(typeName).sliced(8);
        }
    }

    if (isWrapper) {
        qDebug() << "jsvalueToObject_ptr(" <<  waiting_className << ") - returning unwrapped from Variant" << typeName << "pointer of" << wrappedName;
        return (qvariant_cast<wrapper_common*>(variant))->get_selfptr();
    }

    if (waiting_className != nullptr && std::strcmp(waiting_className, typeName) == 0) {
      qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - unwrapped pointer in Variant" << waiting_className << ", returning nullptr";
      return nullptr;
    } else if (std::strcmp("QVariantList", typeName) == 0) {
      QVariantList varlist = variant.toList();
      qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - VariantList type, not '" << waiting_className << "'. Returning nullptr";
      return nullptr;
    } else {
      if (waiting_className != nullptr) {
          qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - different Variant type '" << typeName << "', not '" << waiting_className << "'. Returning nullptr";
      } else {
          qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - different Variant type '" << typeName << "'. Returning nullptr";
      }
      return nullptr;
    }
  }

  // Проверить, вдруг в JSValue находится QMetaObject, являющийся прокси-классом
  QObject* obj = value.toQObject();
  if (obj == nullptr) {
    qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - value is not QObject. Returning nullptr";
    return nullptr;
  }
  const QMetaObject* mobj = obj->metaObject();
  if (mobj == nullptr) {
    qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - value is QObject but not QMetaObject. Returning nullptr";
    return nullptr;
  }
  const char* objName = mobj->className();
  if (objName == nullptr) {
    qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - value is QMetaObject but has no name. Returning nullptr";
    return nullptr;
  }

  bool isWrapper = false;
  QString pureType = objName;
  QString wrapperSign = objName;
  if (wrapperSign.size() > 8) {
      wrapperSign.truncate(8);
      if (QString("wrapper_") == wrapperSign) {
          isWrapper = true;
          pureType = QString(objName).sliced(8);
      }
  }
  if (!isWrapper) {
      qCritical() << "jsvalueToObject_ptr(" <<  waiting_className << ") - value is QMetaObject"<< pureType << "but not wrapper. Returning nullptr";
      return nullptr;
  }

  if (returnType != nullptr) *returnType = pureType;

  if (waiting_className != nullptr && *waiting_className != '\0' && QString(objName) != QString("wrapper_") + QString(waiting_className)) {
    qDebug() << "attention: jsvalueToObject_ptr(" <<  waiting_className << ") - waiting" << waiting_className << "wrapper, but got" << pureType << "wrapper";
  }

  qDebug() << "jsvalueToObject_ptr(" <<  waiting_className << ") - trying to unwrap" << objName;
  void *ptr = (reinterpret_cast<wrapper_common*>(obj))->get_selfptr();
  qDebug() << "jsvalueToObject_ptr(" <<  waiting_className << ") - returning pointer of" << pureType;
  return ptr;
}
