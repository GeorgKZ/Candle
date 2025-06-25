#include <string>

#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QAbstractItemDelegate>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QBoxLayout>
#include <QtGui/QColor>
#include <QtWidgets/QComboBox>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtWidgets/QHeaderView>
#include <QtGui/QIcon>
#include <QtCore/QIODevice>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLayoutItem>
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QSize>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtUiTools/QUiLoader>
#include <QtWidgets/QWidget>

#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>

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

#include "wrapper_Script.h"

QJSValue variantToJSValue(const QVariant& variant, QJSEngine *engine) {
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

QVariant jsvalueToVariant(const QJSValue& value)
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

// #define wfactory(class, name, obj, par) do { if (strcmp(class, #name ) == 0) { 
//  return qjsEngine(par)->toScriptValue< wrapper_##name *>(new wrapper_##name (( name *) object)); } } while(0)


QJSValue wrapper_common::variantToJSValue(const QVariant& variant) const {
    qDebug() << "wrapper_common::variantToJSValue...";
    return ::variantToJSValue(variant, qjsEngine(this));
}

#define wfactory(class, name, obj) do { if (strcmp(class, #name ) == 0) { \
  return qjsEngine(this)->toScriptValue< wrapper_##name *>( new wrapper_##name ( static_cast<name *>(object) ) ); } } while(0)

QJSValue wrapper_common::wrapperFactory(const char *className, void *object) const {

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

  // Кастомные виджеты
  wfactory(className, ColorPicker, object);
  wfactory(className, Slider, object);
  wfactory(className, SliderBox, object);
  wfactory(className, CameraWidget, object);
  wfactory(className, StyledToolButton, object);

  qCritical() << "wrapperFactory("  << className << ") - unknown class name";
  return qjsEngine(this)->toScriptValue<wrapper_QObject*>(new wrapper_QObject((QObject*)object));

}

#define wregister(name) do { se->globalObject().setProperty( #name , se->newQMetaObject<wrapper_##name>() ); } while(0)

WRAPPER_DLL_EXPORT void register_wrappers(QJSEngine *se) {

//  globalEngine = se;

  // Классы Qt

  wregister(QAbstractButton);
  wregister(QAbstractItemDelegate);
  wregister(QAbstractItemView);
  wregister(QAction);

  wregister(QBoxLayout);
  wregister(QVBoxLayout);
  wregister(QHBoxLayout);
  wregister(QGridLayout);

  wregister(QColor);
  wregister(QComboBox);
  wregister(QDir);
  wregister(QDoubleSpinBox);
  wregister(QFile);
  wregister(QHeaderView);
  wregister(QIcon);
  wregister(QIODevice);
  wregister(QLayout);
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

  // Пользовательские виджеты
  wregister(StyledToolButton);
  wregister(CameraWidget);
  wregister(ColorPicker);
  wregister(Slider);
  wregister(SliderBox);
  wregister(IconDelegate);
  wregister(CodeDelegate);

  qDebug() << "register_wrappers - OK";
}


void *jsvalueToObject_ptr(const char *waiting_className, const QJSValue value, QString *returnType) {

  if (value.isNull()) {
    qDebug() << "ERROR: jsvalueToObject_ptr - value is Null. Returning nullptr";
    return nullptr;
  }

  if (value.isUndefined()) {
    qDebug() << "jsvalueToObject_ptr - value is Undefined. Returning nullptr";
    return nullptr;
  }

  // Проверить, вдруг в JSValue находится Variant с простым или прокси-типом
  QVariant variant = value.toVariant();
  if (variant.isValid() && !variant.isNull() && value.toQObject() == nullptr) {
    const char* typeName = variant.typeName();
    if (typeName == nullptr) {
      qCritical() << "jsvalueToObject_ptr - Variant without type. Returning nullptr";
      return nullptr;
    }

    if (strcmp(typeName, "QString") == 0) {
      qDebug() << "jsvalueToObject_ptr - returning QString pointer";
      if (returnType != nullptr) *returnType = "QString";
      return new QString(variant.toString());
    }
    if (strcmp(typeName, "int") == 0) {
      qDebug() << "jsvalueToObject_ptr - returning qint32 pointer";
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
      qDebug() << "jsvalueToObject_ptr - returning QVariantList pointer";
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
        qDebug() << "jsvalueToObject_ptr - returning unwrapped from Variant" << typeName << "pointer of" << wrappedName;
        return (qvariant_cast<wrapper_common*>(variant))->get_selfptr();
    }

    if (waiting_className != nullptr && std::strcmp(waiting_className, typeName) == 0) {
      qCritical() << "jsvalueToObject_ptr - unwrapped pointer in Variant" << waiting_className << ", returning nullptr";
      return nullptr;
    } else if (std::strcmp("QVariantList", typeName) == 0) {
      QVariantList varlist = variant.toList();
      qCritical() << "jsvalueToObject_ptr - VariantList type, not '" << waiting_className << "'. Returning nullptr";
      return nullptr;
    } else {
      if (waiting_className != nullptr) {
          qCritical() << "jsvalueToObject_ptr - different Variant type '" << typeName << "', not '" << waiting_className << "'. Returning nullptr";
      } else {
          qCritical() << "jsvalueToObject_ptr - different Variant type '" << typeName << "'. Returning nullptr";
      }
      return nullptr;
    }
  }

  // Проверить, вдруг в JSValue находится QMetaObject, являющийся прокси-классом
  QObject* obj = value.toQObject();
  if (obj == nullptr) {
    qCritical() << "jsvalueToObject_ptr - value is not QObject. Returning nullptr";
    return nullptr;
  }
  const QMetaObject* mobj = obj->metaObject();
  if (mobj == nullptr) {
    qCritical() << "jsvalueToObject_ptr - value is QObject but not QMetaObject. Returning nullptr";
    return nullptr;
  }
  const char* objName = mobj->className();
  if (objName == nullptr) {
    qCritical() << "jsvalueToObject_ptr - value is QMetaObject but has no name. Returning nullptr";
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
      qCritical() << "jsvalueToObject_ptr - value is QMetaObject"<< pureType << "but not wrapper. Returning nullptr";
      return nullptr;
  }

  if (returnType != nullptr) *returnType = pureType;

  if (waiting_className != nullptr && *waiting_className != '\0' && QString(objName) != QString("wrapper_") + QString(waiting_className)) {
    qDebug() << "attention: jsvalueToObject_ptr - waiting" << waiting_className << "wrapper, but got" << pureType << "wrapper";
  }

  qDebug() << "jsvalueToObject_ptr - trying to unwrap" << objName;
  void *ptr = (static_cast<wrapper_common*>(obj))->get_selfptr();
  qDebug() << "jsvalueToObject_ptr - returning pointer of" << pureType;
  return ptr;
}

QJSValue newScript(QJSEngine *se, QObject* parent)
{
    return se->newQObject(new Script(parent));
}
