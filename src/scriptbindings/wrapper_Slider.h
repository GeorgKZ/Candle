#ifndef WRAPPER_SLIDER_H
#define WRAPPER_SLIDER_H

#include <QtCore/QObject>
#include "slider.h"
#include "wrapper_QSlider.h"

class WRAPPER_DLL_EXPORT wrapper_Slider : public wrapper_QSlider {

    Q_OBJECT

    // Из файла slider.h
public:

  Q_INVOKABLE explicit wrapper_Slider(wrapper_QWidget *parent = nullptr) :
    wrapper_QSlider(new Slider(parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_Slider::constructor(parent)";
  }

  // int currentValue() const;
  Q_INVOKABLE int currentValue() const {
    return get_selfptr()->currentValue();
  }

  // void setCurrentValue(int currentValue);
  Q_INVOKABLE void setCurrentValue(int currentValue) {
    get_selfptr()->setCurrentValue(currentValue);
  }

public:

  // Конструктор из объекта
  wrapper_Slider(Slider *self) :
    wrapper_QSlider(self) {
    qDebug() << "wrapper_Slider::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Получение константного указателя на объект
  const Slider* get_selfptr() const {
    if (wrapper_QSlider::get_selfptr() == nullptr) {
      qCritical() << "wrapper_Slider::get_selfptr - got nullptr";
    }
    return static_cast<const Slider*>(wrapper_QSlider::get_selfptr());
  }

  // Получение указателя на объект
  Slider* get_selfptr() {
    if (wrapper_QSlider::get_selfptr() == nullptr) {
      qCritical() << "wrapper_Slider::get_selfptr - got nullptr";
    }
    return static_cast<Slider*>(wrapper_QSlider::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_Slider() override {
    qDebug() << "wrapper_Slider::destructor";
/*  delete get_selfptr(); */
  }
};

Q_DECLARE_METATYPE(wrapper_Slider)

#endif // WRAPPER_SLIDER_H
