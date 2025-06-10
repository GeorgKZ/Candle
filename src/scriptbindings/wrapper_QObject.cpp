#include "wrapper_QWidget.h"
#include "wrapper_QObject.h"

QJSValue wrapper_QObject::findChild(const QString &aName, Qt::FindChildOptions options) const {
  QWidget* widget = get_selfptr()->findChild<QWidget*>(aName, options);

  if (widget == nullptr) {
    qCritical() << "no child" << aName << "found!!!";
    return QJSValue();
  }
  const char* widgetClass = widget->metaObject()->className();
  qInfo() << "found child class" << widgetClass << "by name" << aName;
  return wrapperFactory(widgetClass, widget);
}
