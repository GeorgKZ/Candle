#ifndef WRAPPER_STYLEDTOOLBUTTON_H
#define WRAPPER_STYLEDTOOLBUTTON_H

#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QToolButton>
#include "styledtoolbutton.h"
#include "wrapper_QWidget.h"
#include "wrapper_QToolButton.h"
#include "wrapper_QColor.h"

class WRAPPER_DLL_EXPORT wrapper_StyledToolButton : public wrapper_QToolButton {

  Q_OBJECT

  // из файла styledtoolbutton.h

  Q_PROPERTY(QJSValue backgroundColor READ backColor      WRITE setBackColor)
  Q_PROPERTY(QJSValue foregroundColor READ foreColor      WRITE setForeColor)
  Q_PROPERTY(QJSValue highlightColor  READ highlightColor WRITE setHighlightColor)
    
public:

  Q_INVOKABLE explicit wrapper_StyledToolButton(wrapper_QWidget *parent = nullptr) :
    wrapper_QToolButton(new StyledToolButton(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_StyledToolButton::constructor(parent)";
  }

  Q_INVOKABLE bool isHover() {
    return get_selfptr()->isHover();
  }

  Q_INVOKABLE QJSValue backColor() const {
    QColor *color = new QColor(get_selfptr()->backColor());
    return wrapperFactory("QColor", color);
  }

  Q_INVOKABLE void setBackColor(const QJSValue &backColor) {
    QColor *color = jsvalueToPointer(QColor, backColor);
    get_selfptr()->setBackColor(*color);
  }

  Q_INVOKABLE QJSValue foreColor() const {
    QColor *color = new QColor(get_selfptr()->foreColor());
    return wrapperFactory("QColor", color);
  }

  Q_INVOKABLE void setForeColor(const QJSValue &foreColor) {
    QColor *color = jsvalueToPointer(QColor, foreColor);
    get_selfptr()->setForeColor(*color);
  }

  Q_INVOKABLE QJSValue highlightColor() const {
    QColor *color = new QColor(get_selfptr()->highlightColor());
    return wrapperFactory("QColor", color);
  }

  Q_INVOKABLE void setHighlightColor(const QJSValue &highlightColor) {
    QColor *color = jsvalueToPointer(QColor, highlightColor);
    get_selfptr()->setForeColor(*color);
  }

public:

  // Конструктор из объекта
  wrapper_StyledToolButton(StyledToolButton *self) :
    wrapper_QToolButton(self) {
    qDebug() << "wrapper_StyledToolButton::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const StyledToolButton* get_selfptr() const {
    if (wrapper_QToolButton::get_selfptr() == nullptr) {
      qCritical() << "wrapper_StyledToolButton::get_selfptr - got nullptr";
    }
    return static_cast<const StyledToolButton*>(wrapper_QToolButton::get_selfptr());
  }

  // Получение указателя на объект
  StyledToolButton* get_selfptr() {
    if (wrapper_QToolButton::get_selfptr() == nullptr) {
      qCritical() << "wrapper_StyledToolButton::get_selfptr - got nullptr";
    }
    return static_cast<StyledToolButton*>(wrapper_QToolButton::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_StyledToolButton() override {
    qDebug() << "wrapper_StyledToolButton::destructor";
  }
};

Q_DECLARE_METATYPE(wrapper_StyledToolButton)

#endif // WRAPPER_STYLEDTOOLBUTTON_H
