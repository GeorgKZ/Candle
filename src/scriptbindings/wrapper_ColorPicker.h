#ifndef WRAPPER_COLORPICKER_H
#define WRAPPER_COLORPICKER_H

#include <QtCore/QObject>
#include "colorpicker.h"
#include "wrapper_QWidget.h"
#include "wrapper_QColor.h"

class WRAPPER_DLL_EXPORT wrapper_ColorPicker : public wrapper_QWidget {

    Q_OBJECT

    // Из файла colorpicker.h
    Q_PROPERTY(int colorInt READ colorInt WRITE setColorInt)

public:
  Q_INVOKABLE explicit wrapper_ColorPicker(wrapper_QWidget *parent = nullptr) :
    wrapper_QWidget(new ColorPicker(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_ColorPicker::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  // QColor color() const
  Q_INVOKABLE QJSValue color() const {
    return wrapperFactory("QColor", new QColor(get_selfptr()->color()));
  }

  Q_INVOKABLE void setColor(const QJSValue value_color) {
    QColor *color = jsvalueToPointer(QColor, value_color);
    get_selfptr()->setColor(*color);
  }

  Q_INVOKABLE int colorInt() const {
    return get_selfptr()->colorInt();
  }

  Q_INVOKABLE void setColorInt(int color) {
    get_selfptr()->setColorInt(color);
  }

Q_SIGNALS:

    void colorSelected(const QJSValue& color);

public:

  // Конструктор из объекта
  wrapper_ColorPicker(ColorPicker *self) :
    wrapper_QWidget(self) {
    qDebug() << "wrapper_ColorPicker::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const ColorPicker* get_selfptr() const {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_ColorPicker::get_selfptr - got nullptr";
    }
    return static_cast<const ColorPicker*>(wrapper_QWidget::get_selfptr());
  }

  // Получение указателя на объект
  ColorPicker* get_selfptr() {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_ColorPicker::get_selfptr - got nullptr";
    }
    return static_cast<ColorPicker*>(wrapper_QWidget::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_ColorPicker() {
    qDebug() << "wrapper_ColorPicker::destructor";
/*  delete get_selfptr(); */
  }
};

Q_DECLARE_METATYPE(wrapper_ColorPicker);

#endif // WRAPPER_COLORPICKER_H
