#include "wrapper_QWidget.h"
#include "wrapper_QObject.h"

QJSValue wrapper_QObject::findChild(const QString &aName, Qt::FindChildOptions options) const {
  QWidget* widget = get_selfptr()->findChild<QWidget*>(aName, options);

  if (widget == nullptr) {
    qCritical() << "no child" << aName << "found!!!";
    return QJSValue();
  }
  qDebug() << "found child class" << widget->metaObject()->className() << "by name" << aName;
  return PointerToJsvalue(widget->metaObject()->className(), widget);
}
