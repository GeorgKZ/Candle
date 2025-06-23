#ifndef WRAPPER_QSLIDER_H
#define WRAPPER_QSLIDER_H

#include <QtCore/QObject>
#include <QtWidgets/QSlider>
#include "wrapper_QWidget.h"

class WRAPPER_DLL_EXPORT wrapper_QSlider : public wrapper_QWidget { // wraper_QAbstractSlider

  Q_OBJECT

  // Из файла qslider.h
  Q_PROPERTY(TickPosition tickPosition
             READ tickPosition
             WRITE setTickPosition)
  Q_PROPERTY(int tickInterval
             READ tickInterval
             WRITE setTickInterval)

public:
  enum TickPosition {
    NoTicks = 0,
    TicksAbove = 1,
    TicksLeft = TicksAbove,
    TicksBelow = 2,
    TicksRight = TicksBelow,
    TicksBothSides = 3
  };
  Q_ENUM(TickPosition)

  // explicit QSlider(QWidget *parent = nullptr)
  Q_INVOKABLE explicit wrapper_QSlider(wrapper_QWidget *parent = nullptr) :
    wrapper_QWidget(new QSlider(parent == nullptr ? nullptr : parent->get_selfptr())) {
      qDebug() << "wrapper_QSlider::constructor(parent=" << (unsigned long long)(parent == nullptr ? nullptr : parent->get_selfptr()) << ")";
  }

  // explicit QSlider(Qt::Orientation orientation, QWidget *parent = nullptr)
  Q_INVOKABLE explicit wrapper_QSlider(Qt::Orientation orientation, wrapper_QWidget *parent = nullptr) :
    wrapper_QWidget(new QSlider(orientation, parent == nullptr ? nullptr : parent->get_selfptr())) {
    qDebug() << "wrapper_QSlider::constructor(orientation, parent)";
  }

  // QSize sizeHint() const override;

  // QSize minimumSizeHint() const override;

  // void setTickPosition(TickPosition position);
  Q_INVOKABLE void setTickPosition(TickPosition position) {
    get_selfptr()->setTickPosition((QSlider::TickPosition)(int)position);
  }

  // TickPosition tickPosition() const;
  Q_INVOKABLE TickPosition tickPosition() const {
    return (TickPosition)(int)get_selfptr()->tickPosition();
  }

  // void setTickInterval(int ti);
  Q_INVOKABLE void setTickInterval(int ti) {
    get_selfptr()->setTickInterval(ti);
  }

  // int tickInterval() const;
  Q_INVOKABLE int tickInterval() const {
    return get_selfptr()->tickInterval();
  }

  // bool event(QEvent *event) override;

  public:

  // Конструктор из объекта
  wrapper_QSlider(QSlider *self) :
    wrapper_QWidget(self) {
    qDebug() << "wrapper_QSlider::constructor(self=" << (unsigned long long)self << ")";
  }

  // Получение константного указателя на объект
  const QSlider* get_selfptr() const {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QSlider::get_selfptr - got nullptr";
    }
    return static_cast<const QSlider*>(wrapper_QWidget::get_selfptr());
  }

  // Получение указателя на объект
  QSlider* get_selfptr() {
    if (wrapper_QWidget::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QSlider::get_selfptr - got nullptr";
    }
    return static_cast<QSlider*>(wrapper_QWidget::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QSlider() {
    qDebug() << "wrapper_QSlider::destructor";
/*  delete get_selfptr(); */
  }
};

#endif // WRAPPER_QSLIDER_H
