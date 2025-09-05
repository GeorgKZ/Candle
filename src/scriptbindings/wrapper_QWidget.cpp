#include <QSize>
#include <QSizePolicy>
#include "wrapper_QWidget.h"
#include "wrapper_QLayout.h"
#include "wrapper_QSize.h"
#include "wrapper_QSizePolicy.h"

QJSValue wrapper_QWidget::layout() const {
  QLayout* layout = get_selfptr()->layout();
  qDebug() << "wrapper_QWidget::layout() ->" << layout->metaObject()->className();
  return PointerToJsvalue(QLayout, layout);
}

// virtual QSize sizeHint() const;
QJSValue wrapper_QWidget::sizeHint() const
{
    return PointerToJsvalue(QSize, new QSize(get_selfptr()->sizeHint()));
}

// virtual QSize minimumSizeHint() const;
QJSValue wrapper_QWidget::minimumSizeHint() const
{
    return PointerToJsvalue(QSize, new QSize(get_selfptr()->minimumSizeHint()));
}

QJSValue wrapper_QWidget::sizePolicy() const
{
    return PointerToJsvalue(QSizePolicy, new QSizePolicy(get_selfptr()->sizePolicy()));
}

void wrapper_QWidget::setSizePolicy(const QJSValue &sizepolicy) {
    get_selfptr()->setSizePolicy(*jsvalueToPointer(QSizePolicy, sizepolicy));
}
